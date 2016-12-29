#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
bmi(cpu *c, addressing_mode am) {
	uint8_t offset = cpu_advance(c);
	printf("\tBMI: offset %0.2x ", offset);

	if (c->p & CPU_FLAG_N) {
		uint16_t rel_addr = c->pc + (0xFF00 | (uint16_t)offset);
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

ADD_INSTRUCTION(0x30, BMI, RELATIVE, bmi);

