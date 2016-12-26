#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "cartridge.h"
#include "util.h"

cartridge *
cartridge_load(const char *filename) {
	FILE *fp = fopen(filename, "r");
	cartridge *cart = NULL;
	if (fp == NULL) {
		fprintf(stderr, "Could not open .nes-file. Reason: '%m'.\n", errno);
		return NULL;
	}

	cart = xmalloc(sizeof(*cart));
	printf("Read %zu bytes from .nes-file.\n", fread(cart, 1, 0x10, fp));
	if (strncmp("NES", cart->label, 4)) {
		fprintf(stderr, "Not a valid .nes-file.\n");
		fclose(fp);
		free(cart);
		return NULL;
	} else {
		cart->mapper_type = (cart->cb2 & 0xf0) + ((cart->cb1 & 0xf0) >> 4);
		printf("#ROM banks: %hhd, #VROM banks: %hhd\n", cart->no_rom_banks, cart->no_vrom_banks);
		printf("%sal mirroring.\n", cart->cb1 & 1 ? "Vertic" : "Horizont");
		printf("Battery-backed RAM: %s\n", cart->cb1 & 2 ? "yes" : "no");
		printf("Trainer present: %s\n", cart->cb1 & 4 ? "yes" : "no");
		printf("Four-screen VRAM layout: %s\n", cart->cb1 & 8 ? "yes" : "no");
		printf("VS-System cartridge: %s\n", cart->cb2 & 1 ? "yes" : "no");
		printf("ROM Mapper Type: %d\n", cart->mapper_type);
		printf("#RAM banks: %hhd\n", cart->no_ram_banks);
		printf("%s\n", cart->pal ? "PAL" : "NTSC");
		printf("Are zero-bytes zero? %s\n", !memcmp(cart->zeros,"\0\0\0\0\0\0",6) ? "yes" : "no");
		if (cart->cb1 & 4) {
			printf("Reading trainer...\n");
			cart->trainer = xmalloc(TRAINER_SIZE);
			printf("Read %zu bytes from .nes-file.\n",
					fread(cart->trainer, 1, TRAINER_SIZE, fp));
		}
		if (cart->no_rom_banks) {
			printf("Reading %d ROM bank%s...\n", cart->no_rom_banks, cart->no_rom_banks == 1 ? "" : "s");
			cart->rom_banks = xmalloc(ROM_BANK_SIZE * cart->no_rom_banks);
			printf("Read %zu bytes from .nes-file.\n",
					fread(cart->rom_banks, cart->no_rom_banks, ROM_BANK_SIZE, fp));
		}
		if (cart->no_vrom_banks) {
			printf("Reading %d VROM bank%s...\n", cart->no_vrom_banks, cart->no_vrom_banks == 1 ? "" : "s");
			cart->vrom_banks = xmalloc(VROM_BANK_SIZE * cart->no_vrom_banks);
			printf("Read %zu bytes from .nes-file.\n",
					fread(cart->vrom_banks, cart->no_vrom_banks, VROM_BANK_SIZE, fp));
		}
	}
	fclose(fp);

	return cart;
}

void
cartridge_destroy(cartridge *cart) {
	if (cart) {
		free(cart->vrom_banks);
		free(cart->rom_banks);
		free(cart);
	}
}
