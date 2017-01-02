#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
dec_zp(cpu *c, addressing_mode am) {
	uint8_t addr = cpu_advance(c);
	uint8_t data = cpu_read(c, addr);

	printf("\tDEC (0x00%0.2x): 0x%0.2x ", addr, data);
	cpu_write(c, addr, data--);
	printf("to 0x%0.2x\n", data);

	cpu_set_z(c, data);
	cpu_set_n(c, data);

	cpu_write(c, addr, data);
}

ADD_INSTRUCTION(0xc6, DEC, ZERO_PAGE, dec_zp);

