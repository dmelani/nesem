#include <stdio.h>
#include "cpu.h"
#include "isa.h"

static void
tay(cpu *c, addressing_mode am) {
	printf("\tTAY: 0x%0.2x -> y \n", c->a);

	c->y = c->a;
	cpu_set_z(c, c->y);
	cpu_set_n(c, c->y);

	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0xa8, TAY, IMPLIED, tay);
