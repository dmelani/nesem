#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
jsr(cpu *c, addressing_mode am) {
	uint8_t low = cpu_advance(c);
	uint8_t high = cpu_advance(c);
	uint16_t addr = low | (high << 8);
	uint16_t ret = c->pc - 1; // Odd, but this is what the 6502 does. Last part of https://en.wikipedia.org/wiki/MOS_Technology_6502#Bugs_and_quirks explains it
	
	printf("\tJSR Dest: 0x%0.4x Ret: 0x%0.4x\n", addr, ret);

	cpu_push(c, ret >> 8);
	cpu_push(c, ret & 0xFF);
	c->pc = addr;

	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0x20, JSR, ABSOLUTE, jsr);

