#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
dex(cpu *c, addressing_mode am) {
	c->x += 0xFFU;

	cpu_set_z(c, c->x);
	cpu_set_n(c, c->x);
	cpu_tick_clock(c); /* Takes one cycle more */

	printf("\tDEX: 0x%0.2x Flags: 0x%0.2x\n", c->x, c->p);
}

ADD_INSTRUCTION(0xca, DEX, IMPLIED, dex);

