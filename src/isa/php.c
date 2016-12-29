#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
php(cpu *c, addressing_mode am) {
	(void) cpu_read(c, c->pc);
	cpu_push(c, c->p);
	printf("\tPHP: P:0x%0.2x, S:0x%0.2x\n", c->p, c->s);
}

ADD_INSTRUCTION(0x08, PHP, IMPLIED, php);

