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

instruction
isa_decode(uint8_t opcode) {
	switch (opcode) {
		case 0x78:
			return SEI;
		case 0x4C: case 0x6C:
			return JMP;
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
