#pragma once
#include <stdint.h>
#include <stddef.h>

typedef enum {
	INSTRUCTION_UNKNOWN,
	ADC,
	AND,
	ASL,
	BCC,
	BCS,
	BEQ,
	BIT,
	BMI,
	BNE,
	BPL,
	BRK,
	BVC,
	BVS,
	CLC,
	CLD,
	CLI,
	CLV,
	CMP,
	CPX,
	CPY,
	DEC,
	DEX,
	DEY,
	EOR,
	INC,
	INX,
	INY,
	JMP,
	JSR,
	LDA,
	LDX,
	LDY,
	LSR,
	NOP,
	ORA,
	PHA,
	PHP,
	PLA,
	PLP,
	ROL,
	ROR,
	RTI,
	RTS,
	SBC,
	SEC,
	SED,
	SEI,
	STA,
	STX,
	STY,
	TAX,
	TAY,
	TSX,
	TXA,
	TXS,
	TYA
} instruction;

typedef enum {
	ADDRESSING_MODE_UNKNOWN,
	ACCUMULATOR,
	IMMEDIATE,
	ABSOLUTE,
	ZERO_PAGE,
	INDEXED_ZERO_PAGE_X,
	INDEXED_ZERO_PAGE_Y,
	INDEXED_ABSOLUTE_X,
	INDEXED_ABSOLUTE_Y,
	IMPLIED,
	RELATIVE,
	INDEXED_INDIRECT,
	INDIRECT_INDEXED,
	ABSOLUTE_INDIRECT
} addressing_mode;

extern const char *addressing_mode_LUT[];
typedef struct cpu cpu;
typedef struct instr {
	uint8_t opcode;
	const char *name;
	addressing_mode mode;
	void (*exec)(cpu *, addressing_mode);
} instr;
size_t isa_op_table(instr ***);

