TARGET				:= mipsel-unknown-elf
CC					:= $(TARGET)-gcc
LD 					:= $(TARGET)-ld
PSP_PRXGEN			:= psp-prxgen

BUILD_DIR			:= build
DIST_DIR 			:= dist
CFLAGS				:= -EL -mabi=eabi -march=mips2 -mtune=mips2 -Iinclude -ffreestanding -nostdlib -Os -G0 -MMD

LOADER   			:= $(BUILD_DIR)/chantage_loader.bin
LOADER_SOURCES		:= $(shell find src/chantage_loader -name '*.c')
LOADER_OBJECTS		:= $(LOADER_SOURCES:%=$(BUILD_DIR)/%.o)
LOADER_LDFLAGS  	:= -T src/flat_binary.ld

CHANTAGE 			:= $(BUILD_DIR)/chantage.prx
CHANTAGE_ELF		:= $(BUILD_DIR)/chantage.elf
CHANTAGE_SOURCES	:= $(shell find src/chantage -name '*.c')
CHANTAGE_OBJECTS	:= $(CHANTAGE_SOURCES:%=$(BUILD_DIR)/%.o)
CHANTAGE_LDFLAGS 	:= -q -T src/elf.ld

.PHONY: all
all: $(LOADER) $(CHANTAGE)

.PHONY: dist
dist: all
	@mkdir -p $(DIST_DIR)/chantage
	cp $(CHANTAGE) $(LOADER) $(DIST_DIR)/chantage
	zip -r $(DIST_DIR)/chantage.zip $(DIST_DIR)/chantage
	rm -rf $(DIST_DIR)/chantage

.PHONY: clean
clean:
	rm -rf $(LOADER_OBJECTS) $(CHANTAGE_OBJECTS)

.PHONY: mrproper
mrproper:
	rm -rf $(BUILD_DIR)

.PHONY: re
re: mrproper all

$(LOADER): $(LOADER_OBJECTS)
	@mkdir -p $(dir $@)
	$(LD) $(LOADER_LDFLAGS) $(LOADER_OBJECTS) -o $@

$(CHANTAGE): $(CHANTAGE_ELF)
	@mkdir -p $(dir $@)
	$(PSP_PRXGEN) $< $@

$(CHANTAGE_ELF): $(CHANTAGE_OBJECTS)
	@mkdir -p $(dir $@)
	$(LD) $(CHANTAGE_LDFLAGS) $(CHANTAGE_OBJECTS) -o $@

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
