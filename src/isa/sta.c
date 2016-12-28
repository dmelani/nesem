#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
sta(cpu *c, addressing_mode am) {
	uint8_t low = cpu_advance(c);
	uint8_t high = cpu_advance(c);
	uint16_t addr = low | (high << 8);
	printf("\tSTA: A 0x%0.2x to addr 0x%0.4x\n", c->a, addr);

	cpu_write(c, addr, c->a);
}

ADD_INSTRUCTION(0x8d, STA, ABSOLUTE, sta);

