#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "util.h"

#define NES_MEM_MAP_SIZE 0x8000
#define NES_RAM_SIZE 0x0800

/* Local function declarations */
static void cpu_powerup(cpu *);

/* Global functions */
cpu *
cpu_create() {
	cpu *c = xmalloc(sizeof(*c));	
	c->ram  = xmalloc(NES_MEM_MAP_SIZE);

	cpu_powerup(c);

	return c;
}

void
cpu_destroy(cpu *c) {
	free(c->ram);
	free(c);
}

void
cpu_reset(cpu *c) {
	/* As per https://wiki.nesdev.com/w/index.php/CPU_power_up_state */
	c->s -= 3;
	c->p |= CPU_FLAG_I;

}

/* Local function definitions */

static void
cpu_powerup(cpu *c) {
	/* As per https://wiki.nesdev.com/w/index.php/CPU_power_up_state */

	c->a = 0;
	c->x = 0;
	c->y = 0;
	c->s = 0xFD;
	c->p = CPU_FLAG_I | CPU_FLAG_B | CPU_FLAG_U;

	memset(c->ram, 0x00, NES_MEM_MAP_SIZE);
	memset(c->ram, 0xFF, NES_RAM_SIZE);
}
