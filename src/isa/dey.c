#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
dey(cpu *c, addressing_mode am) {
	c->y += 0xFFU;

	cpu_set_z(c, c->y);
	cpu_set_n(c, c->y);
	cpu_tick_clock(c); /* Takes one cycle more */

	printf("\tDEY: 0x%0.2x Flags: 0x%0.2x\n", c->y, c->p);
}

ADD_INSTRUCTION(0x88, DEY, IMPLIED, dey);

