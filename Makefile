PROJECT=nesem

SOURCES+=util.c
SOURCES+=nesem.c
SOURCES+=cpu.c
SOURCES+=mapper.c
SOURCES+=cartridge.c
SOURCES+=nrom.c
SOURCES+=isa/isa.c
SOURCES+=isa/bcc.c
SOURCES+=isa/bcs.c
SOURCES+=isa/beq.c
SOURCES+=isa/bit.c
SOURCES+=isa/bmi.c
SOURCES+=isa/bne.c
SOURCES+=isa/bpl.c
SOURCES+=isa/cld.c
SOURCES+=isa/cli.c
SOURCES+=isa/cmp.c
SOURCES+=isa/dex.c
SOURCES+=isa/dey.c
SOURCES+=isa/inc.c
SOURCES+=isa/inx.c
SOURCES+=isa/iny.c
SOURCES+=isa/jmp.c
SOURCES+=isa/jsr.c
SOURCES+=isa/lda.c
SOURCES+=isa/ldx.c
SOURCES+=isa/ldy.c
SOURCES+=isa/lsr.c
SOURCES+=isa/ora.c
SOURCES+=isa/pha.c
SOURCES+=isa/php.c
SOURCES+=isa/pla.c
SOURCES+=isa/plp.c
SOURCES+=isa/rts.c
SOURCES+=isa/sbc.c
SOURCES+=isa/sei.c
SOURCES+=isa/sta.c
SOURCES+=isa/stx.c
SOURCES+=isa/sty.c
SOURCES+=isa/tax.c
SOURCES+=isa/tay.c
SOURCES+=isa/tsx.c
SOURCES+=isa/txs.c
SOURCES+=isa/tya.c

BUILD_DIR=build
INCLUDE=-Iinclude -Isrc
SRC_DIR=src

CC=clang
CFLAGS=-g -c -Wall -Werror $(INCLUDE)

ifeq ($(shell uname -s),CYGWIN_NT-10.0)
	CFLAGS+=-D__ELF__
endif

OBJS=$(SOURCES:%.c=$(BUILD_DIR)/%.o)
DEPS=$(OBJS:%.o=%.d)

all: $(PROJECT)

$(PROJECT): $(BUILD_DIR) $(BUILD_DIR)/$(PROJECT)
	cp $(BUILD_DIR)/$(PROJECT) $@

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)
	@mkdir $(BUILD_DIR)/isa

$(BUILD_DIR)/$(PROJECT): $(OBJS)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	$(CC) $(CFLAGS) -o $@ $<

-include $(DEPS)

clean:
	rm -f $(PROJECT)
	rm -rf $(BUILD_DIR)

