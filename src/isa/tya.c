#include <stdio.h>
#include "cpu.h"
#include "isa.h"

static void
tya(cpu *c, addressing_mode am) {
	printf("\tTYA: 0x%0.2x -> a \n", c->a);

	c->a = c->y;
	cpu_set_z(c, c->a);
	cpu_set_n(c, c->a);

	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0x98, TYA, IMPLIED, tya);
