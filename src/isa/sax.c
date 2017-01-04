#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
sax(cpu *c, addressing_mode am) {
	printf("\tSAX: ");
	uint16_t addr = isa_load_write_addr(c, am);

	uint8_t res = c->a & c->x;
	printf("0x%0.2x & 0x%0.2x = 0x%0.2x -> (0x%0.4x)\n", c->a, c->x, res, addr);
	cpu_write(c, addr, res);
}

/* Undocumented opcodes */
ADD_INSTRUCTION(0x83, SAX, INDEXED_INDIRECT, sax);
ADD_INSTRUCTION(0x87, SAX, ZERO_PAGE, sax);
ADD_INSTRUCTION(0x8f, SAX, ABSOLUTE, sax);
ADD_INSTRUCTION(0x97, SAX, INDEXED_ZERO_PAGE_Y, sax);
