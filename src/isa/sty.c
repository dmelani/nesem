#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
sty_zp(cpu *c, addressing_mode am) {
	uint8_t dest = cpu_advance(c);
	printf("\tSTY: Y 0x%0.2x to addr 0x%0.4x\n", c->y, dest);

	cpu_write(c, dest, c->y);
}

static void
sty(cpu *c, addressing_mode am) {
	uint8_t low = cpu_advance(c);
	uint8_t high = cpu_advance(c);
	uint16_t addr = low | (high << 8);
	printf("\tSTY: Y 0x%0.2x to addr 0x%0.4x\n", c->y, addr);

	cpu_write(c, addr, c->y);
}


ADD_INSTRUCTION(0x84, STY, ZERO_PAGE, sty_zp);
ADD_INSTRUCTION(0x8c, STY, ZERO_PAGE, sty);

