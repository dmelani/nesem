#include <stdint.h>

#include "linker_set.h"
#include "isa.h"
#include "util.h"

const char *instruction_LUT[] = {
	"Unkown",
	"ADC",
	"AND",
	"ASL",
	"BCC",
	"BCS",
	"BEQ",
	"BIT",
	"BMI",
	"BNE",
	"BPL",
	"BRK",
	"BVC",
	"BVS",
	"CLC",
	"CLD",
	"CLI",
	"CLV",
	"CMP",
	"CPX",
	"CPY",
	"DEC",
	"DEX",
	"DEY",
	"EOR",
	"INC",
	"INX",
	"INY",
	"JMP",
	"JSR",
	"LDA",
	"LDX",
	"LDY",
	"LSR",
	"NOP",
	"ORA",
	"PHA",
	"PHP",
	"PLA",
	"PLP",
	"ROL",
	"ROR",
	"RTI",
	"RTS",
	"SBC",
	"SEC",
	"SED",
	"SEI",
	"STA",
	"STX",
	"STY",
	"TAX",
	"TAY",
	"TSX",
	"TXA",
	"TXS",
	"TYA"
};

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

instruction
isa_decode(uint8_t opcode) {
	switch (opcode) {
		case 0x78:
			return SEI;
		case 0x4C: case 0x6C:
			return JMP;
		case 0x81: case 0x85: case 0x8D: case 0x91: case 0x95: case 0x99: case 0x9D:
			return STA;
		default:
			return INSTRUCTION_UNKNOWN;
	}
}

addressing_mode
isa_addressing_mode(uint8_t opcode) {
	switch (opcode) {
		case 0x78:
			return IMPLIED;
		case 0x4C:
			return ABSOLUTE;
		case 0x6C:
			return ABSOLUTE_INDIRECT;
		default:
			return ADDRESSING_MODE_UNKNOWN;
	}
}

static struct instr unknown_instruction = {
	0,
	"Unknown",
	ADDRESSING_MODE_UNKNOWN,
	NULL
};

size_t
isa_op_table(instr **table) {
	instr **t = xmalloc(sizeof(*t) * (UINT8_MAX + 1));

	printf("Setting table to unknown\n");
	for (int i = 0; i <= UINT8_MAX; i++) {
		printf("Setting table[%d] to unknown\n", i);
		t[i] = &unknown_instruction;
	}

	printf("Declaring linker set\n");
	LINKER_SET_DECLARE(ins, instr);
	
	instr **curr_i;
	LINKER_SET_FOREACH(curr_i, ins) {
		printf("Iterating over linker set, %p\n", curr_i);
		printf("Iterating over linker set, %p\n", *curr_i);
		//printf("Adding %s to pos %d in table", (*ins)->name, (*ins)->opcode);
	//	t[(*derp)->opcode] = *derp;
	}

	*table = *t;
	return UINT8_MAX + 1;
}
