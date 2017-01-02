#pragma once
#include <stdint.h>
#include <stddef.h>
#include "linker_set.h"

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

uint8_t isa_load_read(cpu *, addressing_mode);
uint16_t isa_load_write_addr(cpu *, addressing_mode);

#define ADD_INSTRUCTION(opcode, name, mode, func)		\
static instr __ins_##name##_##opcode = {			\
	opcode,	\
	#name,	\
	mode,	\
	func	\
};	\
LINKER_SET_ADD_DATA(ins, __ins_##name##_##opcode)
