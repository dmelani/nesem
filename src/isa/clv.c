#include <stdio.h>
#include "cpu.h"
#include "isa.h"

static void
clv(cpu *c, addressing_mode am) {
	printf("\tCLV: Flags 0x%0.2x -> ", c->p);
	c->p &= ~CPU_FLAG_V;
	printf("0x%0.2x\n", c->p);
	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0xb8, CLV, IMPLIED, clv);
