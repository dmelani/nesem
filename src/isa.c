#include <stdint.h>

#include "linker_set.h"
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
