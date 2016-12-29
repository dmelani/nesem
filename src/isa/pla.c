#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
pla(cpu *c, addressing_mode am) {
	(void) cpu_read(c, c->pc);
	cpu_tick_clock(c);
	c->a = cpu_pull(c);
	printf("\tPLA: A:0x%0.2x, S:0x%0.2x\n", c->a, c->s);
}

ADD_INSTRUCTION(0x68, PLA, IMPLIED, pla);

