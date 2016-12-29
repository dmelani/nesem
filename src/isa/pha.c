#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
pha(cpu *c, addressing_mode am) {
	(void) cpu_read(c, c->pc);
	cpu_push(c, c->a);
	printf("\tPHA: A:0x%0.2x, S:0x%0.2x\n", c->a, c->s);
}

ADD_INSTRUCTION(0x48, PHA, IMPLIED, pha);

