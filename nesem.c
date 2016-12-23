#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"

int
main(int argc, char *argv[]) {

	cpu *cpu = cpu_create();

	printf("Cpu PC %d\n", cpu->pc);

	return EXIT_SUCCESS;
}
