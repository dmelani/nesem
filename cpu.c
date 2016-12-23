#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "util.h"

cpu *
cpu_create() {
	cpu *cpu = xmalloc(sizeof(*cpu));	
	memset(cpu, 0, sizeof(*cpu));

	return cpu;
}
