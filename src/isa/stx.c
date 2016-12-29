#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
stx_zp(cpu *c, addressing_mode am) {
	uint8_t dest = cpu_advance(c);
	printf("\tSTX: X 0x%0.2x to addr 0x%0.4x\n", c->x, dest);

	cpu_write(c, dest, c->x);
}

static void
stx(cpu *c, addressing_mode am) {
	uint8_t low = cpu_advance(c);
	uint8_t high = cpu_advance(c);
	uint16_t addr = low | (high << 8);
	printf("\tSTX: X 0x%0.2x to addr 0x%0.4x\n", c->a, addr);

	cpu_write(c, addr, c->x);
}

ADD_INSTRUCTION(0x86, STX, ZERO_PAGE, stx_zp);
ADD_INSTRUCTION(0x8e, STX, ABSOLUTE, stx);

