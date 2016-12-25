#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "cpu.h"

char cart[256*1024] = {0};

int
main(int argc, char *argv[]) {

	cpu *cpu = cpu_create();

	printf("Cpu PC %d\n", cpu->pc);

		if (argc > 1) {
			FILE *fp = fopen(argv[1], "r");
			if (fp == NULL) {
				fprintf(stderr, "Could not open .nes-file. Reason: '%s'.\n", strerror(errno));
				return EXIT_FAILURE;
			}

			printf("Read %zu bytes from .nes-file.\n", fread(cart, 1024, 256, fp)*1024);
			if (strncmp("NES", cart, 4)) {
				fprintf(stderr, "Not a valid .nes-file.\n");
				return EXIT_FAILURE;
			} else {
				int mapper_type = cart[7] & 0xf0 + cart[6] & 0xf;
				printf("#ROM banks: %hhd, #VROM banks: %hhd\n", cart[4], cart[5]);
				printf("%sal mirroring.\n", cart[6] & 1 ? "Vertic" : "Horizont");
				printf("Battery-backed RAM: %s\n", cart[6] & 2 ? "yes" : "no");
				printf("Trainer present: %s\n", cart[6] & 4 ? "yes" : "no");
				printf("Four-screen VRAM layout: %s\n", cart[6] & 8 ? "yes" : "no");
				printf("VS-System cartridge: %s\n", cart[7] & 1 ? "yes" : "no");
				printf("ROM Mapper Type: %s (%d)\n", mapper_type_name(mapper_type), mapper_type);
				printf("#RAM banks: %hhd\n", cart[8]);
				printf("%s\n", cart[9] & 1 ? "PAL" : "NTSC");
			}
		}

	return EXIT_SUCCESS;
}
