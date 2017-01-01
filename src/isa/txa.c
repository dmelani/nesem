#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
txa(cpu *c, addressing_mode am) {
	printf("\tTXA: Setting S to 0x%2.0x\n", c->x);

	c->a = c->x;
	cpu_set_z(c, c->x);
	cpu_set_n(c, c->x);

	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0x8a, TXA, IMPLIED, txa);

