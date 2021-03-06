#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
stx(cpu *c, addressing_mode am) {
	printf("\tSTX: ");
	uint16_t addr = isa_load_write_addr(c, am);

	printf(" X 0x%0.2x to addr 0x%0.4x\n", c->x, addr);
	cpu_write(c, addr, c->x);
}

ADD_INSTRUCTION(0x86, STX, ZERO_PAGE, stx);
ADD_INSTRUCTION(0x96, STX, INDEXED_ZERO_PAGE_Y, stx);
ADD_INSTRUCTION(0x8e, STX, ABSOLUTE, stx);

