#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "cartridge.h"
#include "mapper.h"

int
main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s rom\n", argv[0]);
		return EXIT_FAILURE;
	}

	cartridge *cart = cartridge_load(argv[1]);
	if (cart == NULL) {
		printf("Failed to load cartridge");
		return EXIT_FAILURE;
	}

	mapper *mapper = mapper_create(cart);
	if (mapper == NULL) {
		printf("Failed to create mapper");
		return EXIT_FAILURE;
	}

	cpu *cpu = cpu_create(mapper);

	cpu_destroy(cpu);
	cartridge_destroy(cart);

	return EXIT_SUCCESS;
}
