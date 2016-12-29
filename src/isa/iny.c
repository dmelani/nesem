#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
iny(cpu *c, addressing_mode am) {
	c->y++;

	c->p &= ~CPU_FLAG_N; // Clear N flag
	c->p |= c->y & CPU_FLAG_N; // Set N flag if x >= 128
	if (c->y == 0) {
		c->p |= CPU_FLAG_Z;
	} else {
		c->p &= ~CPU_FLAG_Z;
	}

	printf("\tINY: 0x%0.2x Flags: 0x%0.2x\n", c->y, c->p);
	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0xc8, INY, IMPLIED, iny);

