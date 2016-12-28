#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "cpu.h"
#include "util.h"

#define NES_MEM_MAP_SIZE 0x10000
#define NES_RAM_SIZE 0x0800

#define NES_CARTRIDGE_MEMORY_SPACE_BEGIN 0x4020

/* Local function declarations */
static void cpu_powerup(cpu *);
static uint16_t cpu_translate_address(cpu *, uint16_t);
static uint16_t cpu_read_reset_vector(cpu *);

/* Global functions */
cpu *
cpu_create(mapper *mapper) {
	cpu *c = xmalloc(sizeof(*c));	
	c->mem  = xmalloc(NES_MEM_MAP_SIZE);
	c->mapper = mapper;
	c->optable_size = isa_op_table(&c->optable);

	cpu_powerup(c);

	return c;
}

void
cpu_destroy(cpu *c) {
	free(c->mem);
	free(c);
}

void
cpu_reset(cpu *c) {
	/* As per https://wiki.nesdev.com/w/index.php/CPU_power_up_state */
	c->s -= 3;
	c->p |= CPU_FLAG_I;

	c->pc = cpu_read_reset_vector(c);
}

void
cpu_run(cpu *c) {
	uint8_t opcode;
	instr *ins;

	while (true) {
		printf("@%llu - ", c->clock);
		opcode = cpu_advance(c);
		
		if (opcode >= c->optable_size) {
			/* Should be impossible */
			printf("Opcode out of range\n");
			return;
		}
		ins = c->optable[opcode];
		
		printf("Processing instruction: %.2x -> %s in addressing mode \"%s\"\n", opcode, ins->name, addressing_mode_LUT[ins->mode]);
		if (ins->exec == NULL) {
			printf("Instruction %s with addressing mode %s not implemented\n", ins->name, addressing_mode_LUT[ins->mode]);
			return;
		}

		ins->exec(c, ins->mode);
	}
}

inline void
cpu_tick_clock(cpu *c) {
	// Timing and PPU handling should be handled here
	c->clock++;
}

inline uint8_t
cpu_advance(cpu *c) {
	return cpu_read(c, c->pc++);
}

uint8_t
cpu_read(cpu *c, uint16_t address) {
	cpu_tick_clock(c);
	if (address >= NES_CARTRIDGE_MEMORY_SPACE_BEGIN) {
		return c->mapper->read(c->mapper, address);
	}

	return c->mem[cpu_translate_address(c, address)];
}

void
cpu_write(cpu *c, uint16_t address, uint8_t data) {
	cpu_tick_clock(c);
	if (address >= NES_CARTRIDGE_MEMORY_SPACE_BEGIN) {
		c->mapper->write(c->mapper, address, data);
		return; 
	}

	c->mem[cpu_translate_address(c, address)] = data;
}

/* Local function definitions */

static void
cpu_powerup(cpu *c) {
	/* As per https://wiki.nesdev.com/w/index.php/CPU_power_up_state */

	c->a = 0;
	c->x = 0;
	c->y = 0;
	c->s = 0xFD;
	c->p = CPU_FLAG_I | CPU_FLAG_B | CPU_FLAG_U;

	memset(c->mem, 0x00, NES_MEM_MAP_SIZE);
	memset(c->mem, 0xFF, NES_RAM_SIZE);

	c->pc = cpu_read_reset_vector(c);

	c->clock = 0;
}

static inline uint16_t
cpu_translate_address(cpu *c, uint16_t address) {
	/*
		Address table gotten from https://wiki.nesdev.com/w/index.php/CPU_memory_map

		Range		Size	Description
		0x0000-0x07FF	0x0800	2KB internal RAM
		0x0800-0x0FFF	0x0800	Mirrors of 0x0000-0x07FF
		0x1000-0x17FF	0x0800	Mirrors of 0x0000-0x07FF
		0x1800-0x1FFF	0x0800	Mirrors of 0x0000-0x07FF
		0x2000-0x2007	0x0008	NES PPU registers
		0x2008-0x3FFF	0x1FF8	Mirrors of 0x2000-0x2007 (repeats every 8 bytes)
		0x4000-0x4017	0x0018	NES APU and I/O registers
		0x4018-0x401F	0x0008	APU and I/O functionality
		0x4020-0xFFFF	0xBFE0	Cartridge space: PRG ROM, PRG RAM, and mapper registers
	*/
	if (address >= NES_CARTRIDGE_MEMORY_SPACE_BEGIN) {
		/* Just return address if in cart space. This will be handled by the mapper */
		return address;
	}

	switch (address >> 12) {
		case 0: // 0x0000 - 0x0FFF
		case 1: // 0x1000 - 0x1FFF
			return address & 0x07FF;
		case 2: // 0x2000 - 0x2FFF
		case 3: // 0x3000 - 0x3FFF
			return 0x2000 | (address & 0x7);
		case 4: // 0x4000- 0x401F
			// Not implemented yet
		default:
			fprintf(stderr, "Address translation failed: %d\n", address);
	}
	
	/* Should not be reached */
	return address;
}

static uint16_t
cpu_read_reset_vector(cpu *c) {
	return cpu_read(c, 0xFFFC) | cpu_read(c, 0xFFFD) << 8;
}
