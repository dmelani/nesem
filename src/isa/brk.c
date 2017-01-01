#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
brk(cpu *c, addressing_mode am) {
	uint8_t flags;
	(void) cpu_advance(c);
	
	printf("\tBRK PC: 0x%0.4x\n", c->pc);

	cpu_push(c, c->pc >> 8);
	cpu_push(c, c->pc & 0xFF);

	flags = c->p;
	flags |= CPU_FLAG_B;
	cpu_push(c, flags);

	if (c->p & CPU_FLAG_I) {
		/* Interrupt occured during BRK */
		c->pc = cpu_read(c, 0xFFFE) | cpu_read(c, 0xFFFF) << 8;
	}

	c->pc = cpu_read(c, 0xFFFE) | cpu_read(c, 0xFFFF) << 8;
}

ADD_INSTRUCTION(0x00, BRK, IMPLIED, brk);

