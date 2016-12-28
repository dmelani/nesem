#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

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

static instr jmp_absolute = {
	0x4C,
	"JMP",
	ABSOLUTE,
	jmp
};
LINKER_SET_ADD_DATA(ins, jmp_absolute);

static instr jmp_absolute_indirect = {
	0x6C,
	"JMP",
	ABSOLUTE_INDIRECT,
	jmp
};
LINKER_SET_ADD_DATA(ins, jmp_absolute_indirect);

