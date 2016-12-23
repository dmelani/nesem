PROJECT=nesem
CC=clang
CFLAGS=-c -Wall -Werror

SOURCES+=nesem.c
SOURCES+=util.c
SOURCES+=cpu.c

OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: $(PROJECT)

$(PROJECT): $(OBJECTS)

clean:
	rm -f $(PROJECT) $(OBJECTS)

