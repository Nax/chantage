DESTDIR 				?= build/dist
DESTDIR_COMMON			:= $(DESTDIR)/PSP/COMMON/ULUS10297
DESTDIR_MODS			:= $(DESTDIR_COMMON)/mods

TARGET					:= mips-unknown-elf
AR						:= $(TARGET)-ar
CC						:= $(TARGET)-gcc
LD						:= $(TARGET)-ld
PSP_PRXGEN				:= psp-prxgen

BUILD_DIR				:= build
CFLAGS					:= -EL -mabi=eabi -march=mips2 -Wall -Iinclude -Isrc -ffreestanding -nostdlib -Os -MMD -pipe
LDFLAGS 				:= -L$(BUILD_DIR)/lib
ARFLAGS					:= rcs

DEPS					:= $(shell find $(BUILD_DIR) -name '*.d' 2>/dev/null)

LIBCHANTAGE				:= $(BUILD_DIR)/lib/libchantage.a
LIBCHANTAGE_OBJECTS		:= $(BUILD_DIR)/src/libchantage.S.o

LIBPRXLOADER			:= $(BUILD_DIR)/lib/libprxloader.a
LIBPRXLOADER_OBJECTS	:= $(BUILD_DIR)/src/prx_loader.c.o

LOADER					:= $(BUILD_DIR)/chantage_loader.bin
LOADER_OBJECTS			:= $(BUILD_DIR)/src/chantage_loader.c.o
LOADER_LDFLAGS			:= $(LDFLAGS) -T src/flat_binary.ld

CHANTAGE				:= $(BUILD_DIR)/chantage.prx
CHANTAGE_ELF			:= $(BUILD_DIR)/chantage.elf
CHANTAGE_SOURCES		:= $(shell find src/chantage -name '*.c' -o -name '*.S')
CHANTAGE_OBJECTS		:= $(CHANTAGE_SOURCES:%=$(BUILD_DIR)/%.o)
CHANTAGE_LDFLAGS		:= $(LDFLAGS) -Xlinker -q -T src/elf.ld

SLOWDOWN				:= $(BUILD_DIR)/mods/slowdown_fix.prx
SLOWDOWN_ELF			:= $(BUILD_DIR)/mods/slowdown_fix.elf
SLOWDOWN_OBJECTS		:= $(BUILD_DIR)/src/slowdown.c.o
SLOWDOWN_LDFLAGS		:= $(CHANTAGE_LDFLAGS)

TESTMOD					:= $(BUILD_DIR)/mods/test_mod.prx
TESTMOD_ELF				:= $(BUILD_DIR)/mods/test_mod.elf
TESTMOD_OBJECTS			:= $(BUILD_DIR)/src/test_mod.c.o
TESTMOD_LDFLAGS			:= $(CHANTAGE_LDFLAGS)

DIST					:= $(BUILD_DIR)/chantage.zip

ALL_TARGETS				:= $(LOADER) $(CHANTAGE) $(SLOWDOWN) $(TESTMOD)

.PHONY: all
all: $(ALL_TARGETS)

-include $(DEPS)

.PHONY: install
install: $(ALL_TARGETS)
	@mkdir -p $(DESTDIR_MODS)
	cp chantage.ppf $(DESTDIR)
	cp $(CHANTAGE) $(LOADER) $(DESTDIR_COMMON)
	cp $(SLOWDOWN) $(TESTMOD) $(DESTDIR_MODS)
	ls -1 $(DESTDIR_MODS) > $(DESTDIR_COMMON)/mods.txt

.PHONY: dist
dist: $(DIST)

$(DIST): $(ALL_TARGETS)
	@mkdir -p $(dir $@)
	TMP=$$(mktemp -d)						\
	&& $(MAKE) install DESTDIR=$$TMP		\
	&& cd $$TMP 							\
	&& zip -r $(abspath $(DIST)) ./ 		\
	&& cd ..								\
	&& rm -rf $$TMP

.PHONY: clean
clean:
	rm -rf $(LOADER_OBJECTS) $(CHANTAGE_OBJECTS)

.PHONY: mrproper
mrproper:
	rm -rf $(BUILD_DIR)

.PHONY: re
re: mrproper all

$(LIBPRXLOADER): $(LIBPRXLOADER_OBJECTS)
	@mkdir -p $(dir $@)
	$(AR) $(ARFLAGS) $@ $(LIBPRXLOADER_OBJECTS)

$(LOADER): $(LOADER_OBJECTS) $(LIBPRXLOADER) $(LIBCHANTAGE)
	@mkdir -p $(dir $@)
	$(LD) $(LOADER_LDFLAGS) $(LOADER_OBJECTS) -L$(BUILD_DIR)/lib -lprxloader -lchantage -o $@

$(CHANTAGE): $(CHANTAGE_ELF)
	@mkdir -p $(dir $@)
	$(PSP_PRXGEN) $< $@

$(CHANTAGE_ELF): $(CHANTAGE_OBJECTS) $(LIBPRXLOADER) $(LIBCHANTAGE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CHANTAGE_LDFLAGS) $(CHANTAGE_OBJECTS) -L$(BUILD_DIR)/lib -lprxloader -lchantage -lgcc -o $@

$(SLOWDOWN): $(SLOWDOWN_ELF)
	@mkdir -p $(dir $@)
	$(PSP_PRXGEN) $< $@

$(SLOWDOWN_ELF): $(SLOWDOWN_OBJECTS) $(LIBCHANTAGE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SLOWDOWN_LDFLAGS) $(SLOWDOWN_OBJECTS) -lchantage -lgcc -o $@

$(TESTMOD): $(TESTMOD_ELF)
	@mkdir -p $(dir $@)
	$(PSP_PRXGEN) $< $@

$(TESTMOD_ELF): $(TESTMOD_OBJECTS) $(LIBCHANTAGE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TESTMOD_LDFLAGS) $(TESTMOD_OBJECTS) -lchantage -lgcc -o $@

$(LIBCHANTAGE): $(LIBCHANTAGE_OBJECTS)
	@mkdir -p $(dir $@)
	$(AR) $(ARFLAGS) $@ $(LIBCHANTAGE_OBJECTS)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.S.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
