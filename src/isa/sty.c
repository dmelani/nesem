#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
sty(cpu *c, addressing_mode am) {
	uint8_t addr = isa_load_read(c, am);

	printf("\tSTY: A 0x%0.2x to addr 0x%0.4x\n", c->y, addr);
	cpu_write(c, addr, c->y);
}

ADD_INSTRUCTION(0x84, STY, ZERO_PAGE, sty);
ADD_INSTRUCTION(0x94, STY, INDEXED_ZERO_PAGE_X, sty);
ADD_INSTRUCTION(0x8c, STY, ABSOLUTE, sty);

