#include <stdint.h>

#include "cpu.h"
#include "isa.h"
#include "util.h"

const char *addressing_mode_LUT[] = {
	"Unknown",
	"Accumulator",
	"Immediate",
	"Absolute",
	"Zero page",
	"Indexed zero page x",
	"Indexed zero page y",
	"Indexed absolute x",
	"Indexed absolute y",
	"Implied",
	"Relative",
	"Indexed indirect",
	"Indirect indexed",
	"Absolute indirect"
};

static struct instr unknown_instruction = {
	0,
	"Unknown",
	ADDRESSING_MODE_UNKNOWN,
	NULL
};

size_t
isa_op_table(instr ***table) {
	instr **t = xmalloc(sizeof(*t) * (UINT8_MAX + 1));

	printf("Setting table to unknown\n");
	for (int i = 0; i <= UINT8_MAX; i++) {
		t[i] = &unknown_instruction;
	}

	LINKER_SET_DECLARE(ins, instr);
	
	instr **curr_i;
	LINKER_SET_FOREACH(curr_i, ins) {
		printf("Adding %s to pos %d (0x%0.2x) in table\n", (*curr_i)->name, (*curr_i)->opcode, (*curr_i)->opcode);
		t[(*curr_i)->opcode] = *curr_i;
	}

	*table = t;
	return UINT8_MAX + 1;
}

uint8_t
isa_load_read(cpu *c, addressing_mode am) {
	uint8_t data = cpu_advance(c);
	uint8_t low;
	uint8_t high;
	uint8_t addr;
	uint8_t zpa;

	/* Load */
	switch (am) {
		case IMMEDIATE:
			printf("#0x%0.2x ", data);
			return data;
		case ABSOLUTE:
			low = data;
			addr = low | (cpu_advance(c) << 8);

			break;
		case ZERO_PAGE:
			addr = data;

			break;
		case INDEXED_ZERO_PAGE_X:
			low = data;

			low = cpu_read(c, low); 
			low += c->x;

			addr = low;

			break;
		case INDEXED_ABSOLUTE_X:
			low = data;
			high = cpu_advance(c);

			addr = (low | (high << 8)) + c->x;
			if (addr >> 8 != high) {
				printf("+");
				cpu_read(c, (high << 8) | (addr & 0xFF));
			}

			break;
		case INDEXED_ABSOLUTE_Y:
			low = data;
			high = cpu_advance(c);

			addr = (low | (high << 8)) + c->y;
			if (addr >> 8 != high) {
				printf("+");
				cpu_read(c, (high << 8) | (addr & 0xFF));
			}

			break;
		case INDEXED_INDIRECT:
			zpa = data;
			cpu_read(c, zpa);
			zpa += c->x;

			low = cpu_read(c, zpa++);
			high = cpu_read(c, zpa);

			addr = (low | (high << 8));
		
			break;
		case INDIRECT_INDEXED:
			zpa = data;
			cpu_read(c, zpa);

			low = cpu_read(c, zpa++);
			high = cpu_read(c, zpa);

			addr = (low | (high << 8)) + c->y;
			if (addr >> 8 != high) {
				printf("+");
				cpu_read(c, (high << 8) | (addr & 0xFF));
			}

			break;
		default:
			printf("UNHANDLED ADDRESSING MODE\n");
			return 0;
	}
	
	data = cpu_read(c, addr);
	printf("(0x%0.4x) ", data);
	return data;
}
