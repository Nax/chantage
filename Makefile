TARGET					:= mips-unknown-elf
AR						:= $(TARGET)-ar
CC						:= $(TARGET)-gcc
LD						:= $(TARGET)-ld
PSP_PRXGEN				:= psp-prxgen

BUILD_DIR				:= build
CFLAGS					:= -EL -mabi=eabi -march=mips2 -Iinclude -Isrc -ffreestanding -nostdlib -Os -MMD -pipe
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

DIST_DIR				:= dist
DIST					:= $(DIST_DIR)/chantage.zip
DIST_TMP				:= $(DIST_DIR)/tmp
DIST_PSPDIR				:= $(DIST_TMP)/PSP/COMMON/ULUS10297
DIST_MODSDIR			:= $(DIST_PSPDIR)/mods

.PHONY: all
all: $(LOADER) $(CHANTAGE) $(SLOWDOWN)

-include $(DEPS)

.PHONY: dist
dist: $(DIST)

$(DIST): $(LOADER) $(CHANTAGE) $(SLOWDOWN)
	@mkdir -p $(DIST_MODSDIR)
	rm -rf $(DIST)
	cp chantage.ppf $(DIST_TMP)
	cp $(CHANTAGE) $(LOADER) $(DIST_PSPDIR)
	cp $(SLOWDOWN) $(DIST_MODSDIR)
	ls -1 $(DIST_MODSDIR) > $(DIST_PSPDIR)/mods.txt
	cd $(DIST_TMP) && zip -r ../chantage.zip PSP chantage.ppf
	rm -rf $(DIST_TMP)

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

$(LIBCHANTAGE): $(LIBCHANTAGE_OBJECTS)
	@mkdir -p $(dir $@)
	$(AR) $(ARFLAGS) $@ $(LIBCHANTAGE_OBJECTS)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.S.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
