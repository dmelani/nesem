#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
rti(cpu *c, addressing_mode am) {
	uint16_t addr;
	uint8_t flags;

	(void) cpu_advance(c);

	flags = cpu_pull(c);
	/* Do we need to do something if B flag is set? */
	cpu_set_p(c, flags);
	uint8_t low = cpu_pull(c);
	uint8_t high = cpu_pull(c);

	addr = low | (high << 8);
	c->pc = addr;

	printf("\tRTI Ret: 0x%0.4x\n", c->pc);
}

ADD_INSTRUCTION(0x40, RTI, IMPLIED, rti);

