#include <stdio.h>

#include "mapper.h"
#include "cartridge.h"
#include "util.h"

typedef struct nrom_mapper {
	mapper mapper;
	cartridge *cart;
} nrom_mapper;

static uint8_t
read(mapper *mapper, uint16_t address) {
	//nrom_mapper *state = (nrom_mapper *) mapper;
	return 0;
}

static void
write(mapper *mapper, uint16_t address, uint8_t data) {
	//nrom_mapper *state = (nrom_mapper *) mapper;
	return;
}

mapper *
mapper_nrom_create(cartridge *cart) {
	printf("Creating NROM mapper\n");
	nrom_mapper *nrom = xmalloc(sizeof(*nrom));	

	nrom->mapper.read = read;
	nrom->mapper.write = write;
	nrom->cart = cart;

	return &nrom->mapper;
}
