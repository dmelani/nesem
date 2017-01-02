#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
inc(cpu *c, addressing_mode am) {
	printf("\tINC: ");
	uint16_t addr = isa_load_read_write_addr(c, am);
	uint8_t data = cpu_read(c, addr);

	printf("(0x%0.4x) 0x%0.2x ", addr, data);
	cpu_write(c, addr, data++);
	printf("to 0x%0.2x\n", data);

	cpu_set_z(c, data);
	cpu_set_n(c, data);

	cpu_write(c, addr, data);
}

ADD_INSTRUCTION(0xe6, INC, ZERO_PAGE, inc);
ADD_INSTRUCTION(0xf6, INC, INDEXED_ZERO_PAGE_X, inc);
ADD_INSTRUCTION(0xee, INC, ABSOLUTE, inc);
ADD_INSTRUCTION(0xfe, INC, INDEXED_ABSOLUTE_X, inc);

