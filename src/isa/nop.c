#include <stdio.h>
#include "cpu.h"
#include "isa.h"

static void
nop(cpu *c, addressing_mode am) {
	printf("\tNOP\n");
	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0xea, NOP, IMPLIED, nop);
