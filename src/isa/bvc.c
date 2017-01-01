#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
bvc(cpu *c, addressing_mode am) {
	int8_t offset = cpu_advance(c);
	printf("\tBVC: offset %0.2x Flag: 0x%0.2x ", offset, c->p);

	if (c->p & CPU_FLAG_V == 0) {
		uint16_t rel_addr = c->pc + offset;
		cpu_tick_clock(c);
		
		/* Increment clock if ending up on new page */ 
		if ((rel_addr & 0xFF00) != (c->pc & 0xFF00))
			cpu_tick_clock(c);

		c->pc = rel_addr;
		printf(" branch to 0x%0.4x\n", c->pc);

		return;
	}

	printf("not branching\n");
}

ADD_INSTRUCTION(0x70, BVS, RELATIVE, bvs);

