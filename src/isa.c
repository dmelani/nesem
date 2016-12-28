#include <stdint.h>

#include "linker_set.h"
#include "isa.h"
#include "util.h"
#include "cpu.h"

static void sei(cpu *c, addressing_mode am);
static void jmp(cpu *c, addressing_mode am);

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

static instr *op_table[UINT8_MAX + 1] = {
	&(instr){0x00, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x01, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x02, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x03, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x04, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x05, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x06, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x07, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x08, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x09, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x0a, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x0b, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x0c, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x0d, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x0e, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x0f, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x10, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x11, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x12, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x13, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x14, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x15, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x16, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x17, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x18, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x19, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x1a, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x1b, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x1c, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x1d, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x1e, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x1f, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x20, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x21, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x22, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x23, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x24, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x25, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x26, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x27, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x28, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x29, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x2a, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x2b, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x2c, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x2d, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x2e, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x2f, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x30, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x31, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x32, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x33, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x34, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x35, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x36, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x37, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x38, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x39, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x3a, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x3b, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x3c, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x3d, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x3e, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x3f, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x40, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x41, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x42, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x43, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x44, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x45, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x46, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x47, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x48, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x49, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x4a, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x4b, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x4c, "JMP", ABSOLUTE, jmp},
	&(instr){0x4d, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x4e, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x4f, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x50, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x51, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x52, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x53, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x54, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x55, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x56, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x57, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x58, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x59, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x5a, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x5b, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x5c, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x5d, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x5e, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x5f, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x60, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x61, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x62, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x63, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x64, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x65, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x66, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x67, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x68, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x69, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x6a, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x6b, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x6c, "JMP", ABSOLUTE_INDIRECT, jmp},
	&(instr){0x6d, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x6e, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x6f, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x70, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x71, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x72, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x73, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x74, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x75, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x76, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x77, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x78, "SEI", IMPLIED, sei},
	&(instr){0x79, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x7a, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x7b, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x7c, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x7d, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x7e, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x7f, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x80, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x81, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x82, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x83, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x84, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x85, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x86, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x87, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x88, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x89, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x8a, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x8b, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x8c, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x8d, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x8e, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x8f, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x90, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x91, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x92, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x93, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x94, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x95, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x96, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x97, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x98, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x99, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x9a, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x9b, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x9c, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x9d, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x9e, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0x9f, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xa0, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xa1, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xa2, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xa3, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xa4, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xa5, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xa6, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xa7, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xa8, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xa9, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xaa, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xab, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xac, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xad, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xae, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xaf, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xb0, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xb1, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xb2, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xb3, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xb4, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xb5, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xb6, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xb7, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xb8, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xb9, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xba, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xbb, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xbc, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xbd, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xbe, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xbf, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xc0, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xc1, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xc2, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xc3, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xc4, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xc5, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xc6, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xc7, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xc8, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xc9, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xca, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xcb, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xcc, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xcd, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xce, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xcf, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xd0, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xd1, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xd2, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xd3, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xd4, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xd5, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xd6, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xd7, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xd8, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xd9, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xda, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xdb, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xdc, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xdd, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xde, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xdf, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xe0, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xe1, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xe2, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xe3, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xe4, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xe5, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xe6, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xe7, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xe8, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xe9, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xea, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xeb, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xec, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xed, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xee, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xef, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xf0, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xf1, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xf2, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xf3, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xf4, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xf5, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xf6, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xf7, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xf8, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xf9, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xfa, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xfb, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xfc, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xfd, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xfe, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL},
	&(instr){0xff, "Unknown", ADDRESSING_MODE_UNKNOWN, NULL}
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


static void
sei(cpu *c, addressing_mode am) {
	c->p |= CPU_FLAG_I;
	cpu_tick_clock(c); /* Takes one cycle more */
}

static void
jmp(cpu *c, addressing_mode am) {
	uint8_t low = cpu_advance(c);
	uint8_t high = cpu_advance(c);
	uint16_t addr = low | (high << 8);
	printf("JMP %0.4x : high %0.2x low %0.2x\n", addr, high, low);

	if (am == ABSOLUTE_INDIRECT) {
		low = cpu_read(c, addr);
		high = cpu_read(c, addr+1);
		addr = low | (high << 8);
		printf("ABSOLUTE INDIRECT JMP %0.4x : high %0.2x low %0.2x\n", addr, high, low);
	}

	c->pc = addr;
}

size_t
isa_op_table(instr ***table) {
	*table = op_table;

	return UINT8_MAX + 1;
}
