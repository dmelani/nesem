#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
sta(cpu *c, addressing_mode am) {
	uint8_t low = cpu_advance(c);
	uint8_t high = cpu_advance(c);
	uint16_t addr = low | (high << 8);

	printf("\tSTA: A 0x%0.2x to addr 0x%0.4x\n", c->a, addr);

	cpu_write(c, addr, c->a);
}

static void
sta_indirect_indexed(cpu *c, addressing_mode am) {
	uint8_t zpa = cpu_advance(c);
	uint16_t addr = cpu_read_paged_16(c, zpa);
	addr += c->y;

	printf("\tSTA (0x%0.2x),0x%0.2x: A 0x%0.2x to addr 0x%0.4x\n", zpa, c->y, c->a, addr);
	cpu_read(c, addr);
	cpu_write(c, addr, c->a);
}

static void
sta_zero_page_x(cpu *c, addressing_mode am) {
	uint8_t zpa = cpu_advance(c);
	uint8_t addr;

	/* This is what it does according to http://nesdev.com/6502_cpu.txt */
	cpu_read(c, zpa);
	addr = zpa + c->x;

	printf("\tSTA (0x%0.2x),0x%0.2x: A 0x%0.2x to addr 0x%0.4x\n", zpa, c->x, c->a, addr);
	cpu_write(c, addr, c->a);
}

static void
sta_absolute_x(cpu *c, addressing_mode am) {
	uint8_t low = cpu_advance(c);
	uint8_t high = cpu_advance(c);
	uint16_t addr;

	uint8_t ea_low = low + c->x;
	addr = ea_low | (high << 8);
	cpu_read(c, addr);

	printf("\tSTA (0x%0.2x),0x%0.2x: A 0x%0.2x to addr 0x%0.4x\n", low | (high << 8), c->x, c->a, addr);

	cpu_write(c, addr, c->a);
}

ADD_INSTRUCTION(0x8d, STA, ABSOLUTE, sta);
ADD_INSTRUCTION(0x91, STA, INDIRECT_INDEXED, sta_indirect_indexed);
ADD_INSTRUCTION(0x95, STA, INDEXED_ZERO_PAGE_X, sta_zero_page_x);
ADD_INSTRUCTION(0x9d, STA, INDEXED_ABSOLUTE_X, sta_absolute_x);

