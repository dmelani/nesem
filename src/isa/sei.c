#include "cpu.h"
#include "isa.h"

static void
sei(cpu *c, addressing_mode am) {
	c->p |= CPU_FLAG_I;
	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0x78, SEI, IMPLIED, sei);
