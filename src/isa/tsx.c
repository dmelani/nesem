#include <stdio.h>
#include "cpu.h"
#include "isa.h"

static void
tsx(cpu *c, addressing_mode am) {
	printf("\tTSX: 0x%0.2x -> x \n", c->s);

	c->x = c->s;
	cpu_set_z(c, c->x);
	cpu_set_n(c, c->x);

	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0xba, TSX, IMPLIED, tsx);
