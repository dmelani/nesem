#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
plp(cpu *c, addressing_mode am) {
	(void) cpu_read(c, c->pc);
	cpu_tick_clock(c);
	c->p = cpu_pull(c);
	printf("\tPLP: P:0x%0.2x, S:0x%0.2x\n", c->p, c->s);
}

ADD_INSTRUCTION(0x28, PLP, IMPLIED, plp);

