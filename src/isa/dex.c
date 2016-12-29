#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
dex(cpu *c, addressing_mode am) {
	c->x += 0xFFU;

	c->p &= ~CPU_FLAG_N; // Clear N flag
	c->p |= c->x & CPU_FLAG_N; // Set N flag if x >= 128
	if (c->x == 0) {
		c->p |= CPU_FLAG_Z;
	} else {
		c->p &= ~CPU_FLAG_Z;
	}
	cpu_tick_clock(c); /* Takes one cycle more */

	printf("\tDEX: 0x%0.2x Flags: 0x%0.2x\n", c->x, c->p);
}

ADD_INSTRUCTION(0xca, DEX, IMPLIED, dex);

