#include <stdio.h>
#include "cpu.h"
#include "isa.h"

static void
tax(cpu *c, addressing_mode am) {
	printf("\tTAX: 0x%0.2x -> x \n", c->a);

	c->x = c->a;
	cpu_set_z(c, c->x);
	cpu_set_n(c, c->x);

	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0xaa, TAX, IMPLIED, tax);
