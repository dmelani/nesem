#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
dec(cpu *c, addressing_mode am) {
	printf("\tDEC: ");
	uint16_t addr = isa_load_read_write_addr(c, am);
	uint8_t data = cpu_read(c, addr);

	printf("(0x%0.4x) 0x%0.2x ", addr, data);
	cpu_write(c, addr, data--);
	printf("to 0x%0.2x\n", data);

	cpu_set_z(c, data);
	cpu_set_n(c, data);

	cpu_write(c, addr, data);
}

ADD_INSTRUCTION(0xc6, DEC, ZERO_PAGE, dec);
ADD_INSTRUCTION(0xd6, DEC, INDEXED_ZERO_PAGE_X, dec);
ADD_INSTRUCTION(0xce, DEC, ABSOLUTE, dec);
ADD_INSTRUCTION(0xde, DEC, INDEXED_ABSOLUTE_X, dec);

