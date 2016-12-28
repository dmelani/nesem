#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
txs(cpu *c, addressing_mode am) {
	printf("\tTXS: Setting S to 0x%2.0x\n", c->x);
	c->s = c->x;
	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0x9a, TXS, IMPLIED, txs);

