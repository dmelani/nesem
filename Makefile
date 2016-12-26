PROJECT=nesem
CC=clang
CFLAGS=-g -c -Wall -Werror

SOURCES+=nesem.c
SOURCES+=util.c
SOURCES+=cpu.c
SOURCES+=mapper.c
SOURCES+=cartridge.c
SOURCES+=nrom.c

OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: $(PROJECT)

$(PROJECT): $(OBJECTS)

clean:
	rm -f $(PROJECT) $(OBJECTS)

