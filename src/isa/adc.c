#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
adc(cpu *c, addressing_mode am) {
	printf("\tADC: ");
	uint8_t data = isa_load_read(c);

	uint8_t carry = c->p & CPU_FLAG_C;
	uint16_t tmp = c->a + data + (carry ? 1 : 0);

	printf("0x%0.2x + 0x%0.2x + 0x%0.1x = ", c->a, data, carry ? 1 : 0);

	cpu_set_n(c, tmp & 0xFF);
	cpu_set_z(c, tmp & 0xFF);

	if (!((c->a ^ tmp) & 0x80) && ((c->a ^ data) & 0x80)) {
		c->p |= CPU_FLAG_V;
	} else {
		c->p &= ~CPU_FLAG_V;
	}

	if (tmp > 0xFF) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}

	c->a = tmp & 0xFF;
	printf("0x%0.2x Flags: 0x%0.2x\n",  c->a, c->p);
}

ADD_INSTRUCTION(0x69, ADC, IMMEDIATE, adc);
ADD_INSTRUCTION(0x65, ADC, ZERO_PAGE, adc);
ADD_INSTRUCTION(0x75, ADC, INDEXED_ZERO_PAGE_X, adc);
ADD_INSTRUCTION(0x6d, ADC, ABSOLUTE, adc);
ADD_INSTRUCTION(0x7d, ADC, INDEXED_ABSOLUTE_X, adc);
ADD_INSTRUCTION(0x79, ADC, INDEXED_ZERO_PAGE_Y, adc);
ADD_INSTRUCTION(0x61, ADC, INDEXED_INDIRECT, adc);
ADD_INSTRUCTION(0x71, ADC, INDIRECT_INDEXED, adc);

