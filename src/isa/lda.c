#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
lda(cpu *c, addressing_mode am) {
	uint8_t data = cpu_advance(c);
	c->a = data;

	cpu_set_n(c, data);
	cpu_set_z(c, data);

	printf("\tLDA: 0x%0.2x Flags: 0x%0.2x\n", data, c->p);
}

ADD_INSTRUCTION(0xa9, LDA, IMMEDIATE, lda);

