#include <stdio.h>
#include "cpu.h"
#include "isa.h"

static void
cld(cpu *c, addressing_mode am) {
	printf("\tCLD: Flags 0x%0.2x -> ", c->p);
	c->p &= ~CPU_FLAG_D;
	printf("0x%0.2x\n", c->p);
	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0xD8, CLD, IMPLIED, cld);
