#include <stdint.h>

#include "isa.h"

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
