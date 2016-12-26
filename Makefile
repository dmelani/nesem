PROJECT=nesem
CC=clang
CFLAGS=-g -c -Wall -Werror
BUILD_DIR=build
SRC_DIR=src

SOURCES+=util.c
SOURCES+=nesem.c
SOURCES+=cpu.c
SOURCES+=mapper.c
SOURCES+=cartridge.c
SOURCES+=nrom.c
SOURCES+=isa.c

OBJS=$(SOURCES:%.c=$(BUILD_DIR)/%.o)
DEPS=$(OBJS:%.o=%.d)

all: $(PROJECT)

$(PROJECT): $(BUILD_DIR) $(BUILD_DIR)/$(PROJECT)
	cp $(BUILD_DIR)/$(PROJECT) $@

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)

$(BUILD_DIR)/$(PROJECT): $(OBJS)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	$(CC) $(CFLAGS) -o $@ $<

-include $(DEPS)

clean:
	rm -f $(PROJECT)
	rm -rf $(BUILD_DIR)

