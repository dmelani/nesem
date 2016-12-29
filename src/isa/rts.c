#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
rts(cpu *c, addressing_mode am) {
	uint16_t addr;

	(void) cpu_advance(c);

	uint8_t low = cpu_pull(c);
	uint8_t high = cpu_pull(c);

	addr = low | (high << 8);
	c->pc = addr;
	cpu_tick_clock(c); /* Takes one cycle more */

	c->pc++;
	cpu_tick_clock(c); /* Takes one cycle more */

	printf("\tRST Ret: 0x%0.4x\n", c->pc);
}

ADD_INSTRUCTION(0x60, RTS, IMPLIED, rts);

