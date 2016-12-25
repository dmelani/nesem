#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "cartridge.h"

int
main(int argc, char *argv[]) {

	cpu *cpu = cpu_create();
	cartridge *cart = NULL;

	printf("Cpu PC %d\n", cpu->pc);

	if (argc > 1) {
		cart = cartridge_load(argv[1]);
	}

	cpu_destroy(cpu);
	cartridge_destroy(cart);

	return EXIT_SUCCESS;
}
