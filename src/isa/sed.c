#include <stdio.h>
#include "cpu.h"
#include "isa.h"

static void
sed(cpu *c, addressing_mode am) {
	printf("\tSED: Flags 0x%0.2x -> ", c->p);
	c->p |= CPU_FLAG_D;
	printf("0x%0.2x\n", c->p);
	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0xf8, SED, IMPLIED, sed);
