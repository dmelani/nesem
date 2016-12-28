#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
lda(cpu *c, addressing_mode am) {
	uint8_t data = cpu_advance(c);
	c->a = data;

	c->p &= ~CPU_FLAG_N; // Clear N flag
	c->p |= data & CPU_FLAG_N; // Set N flag if x >= 128
	if (data == 0) {
		c->p |= CPU_FLAG_Z;
	} else {
		c->p &= ~CPU_FLAG_Z;
	}

	printf("\tLDA: 0x%0.2x Flags: 0x%2.0x\n", data, c->p);
}

ADD_INSTRUCTION(0xa9, LDA, IMMEDIATE, lda);

