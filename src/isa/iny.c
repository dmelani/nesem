#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
iny(cpu *c, addressing_mode am) {
	c->y++;

	cpu_set_z(c, c->y);
	cpu_set_n(c, c->y);

	printf("\tINY: 0x%0.2x Flags: 0x%0.2x\n", c->y, c->p);
	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0xc8, INY, IMPLIED, iny);
