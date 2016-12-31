#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
jmp(cpu *c, addressing_mode am) {
	uint8_t low = cpu_advance(c);
	uint8_t high = cpu_advance(c);
	uint16_t addr = low | (high << 8);

	if (am == ABSOLUTE_INDIRECT)
		addr = cpu_read_paged_16(c, addr);

	printf("\tJMP %0.4x : high %0.2x low %0.2x\n", addr, high, low);
	c->pc = addr;
}

ADD_INSTRUCTION(0x4C, JMP, ABSOLUTE, jmp);
ADD_INSTRUCTION(0x6C, JMP, ABSOLUTE_INDIRECT, jmp);

