#include <stdlib.h>
#include <stdio.h>

#include "mapper.h"
#include "cartridge.h"
#include "util.h"

typedef struct bank {
	uint16_t size;
	uint8_t *data;
} bank;

typedef struct nrom_mapper {
	mapper mapper;
	cartridge *cart;
	bank ram;
	bank lower;
	bank upper;
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

static void
destroy(mapper *mapper) {
	/* Don't free cart. Not owned by us. */
	nrom_mapper *state = (nrom_mapper *) mapper;

	printf("Destroying NROM mapper\n");
	free(state);
}

mapper *
mapper_nrom_create(cartridge *cart) {
	printf("Creating NROM mapper\n");
	nrom_mapper *nrom = xmalloc(sizeof(*nrom));	

	nrom->mapper.read = read;
	nrom->mapper.write = write;
	nrom->mapper.destroy = destroy;
	nrom->cart = cart;

	return &nrom->mapper;
}
