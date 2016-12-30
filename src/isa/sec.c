#include <stdio.h>
#include "cpu.h"
#include "isa.h"

static void
sec(cpu *c, addressing_mode am) {
	printf("\tSEC: Flags 0x%0.2x -> ", c->p);
	c->p |= CPU_FLAG_C;
	printf("0x%0.2x\n", c->p);
	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0x38, SEC, IMPLIED, sec);
