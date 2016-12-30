#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
lsr(cpu *c, addressing_mode am) {
	printf("\tLSR: A: 0x%0.2x -> ",  c->a);

	if (c->a & 0x01) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}
	c->a >>= 1;

	cpu_set_n(c, c->a);
	cpu_set_z(c, c->a);

	cpu_tick_clock(c);

	printf("0x%0.2x Flags: 0x%0.2x\n",  c->a, c->p);
}

ADD_INSTRUCTION(0x4a, LSR, IMMEDIATE, lsr);

