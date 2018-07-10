TARGET				:= mipsel-unknown-elf
AS 					:= $(TARGET)-as
CC					:= $(TARGET)-gcc
LD 					:= $(TARGET)-ld

BUILD_DIR			:= build

LOADER   			:= $(BUILD_DIR)/chantage_loader.bin
LOADER_SOURCES		:= $(shell find src/chantage_loader -name '*.S')
LOADER_OBJECTS		:= $(LOADER_SOURCES:%.S=$(BUILD_DIR)/%.o)
LOADER_CFLAGS		:= -EL -mabi=eabi -march=mips2 -mtune=mips2 -Iinclude -ffreestanding -nostdlib -Os
LOADER_LDFLAGS  	:= -T src/flat_binary.ld

CHANTAGE			:= $(BUILD_DIR)/chantage.elf
CHANTAGE_SOURCES	:= $(shell find src/chantage -name '*.c')
CHANTAGE_OBJECTS	:= $(CHANTAGE_SOURCES:%.c=$(BUILD_DIR)/%.o)
CHANTAGE_CFLAGS		:= -EL -mabi=eabi -march=mips2 -mtune=mips2 -Iinclude -ffreestanding -nostdlib -Os
CHANTAGE_LDFLAGS 	:= -r -T src/elf.ld

.PHONY: all
all: $(LOADER) $(CHANTAGE)

.PHONY: clean
clean:
	rm -rf $(LOADER_OBJECTS)

.PHONY: mrproper
mrproper:
	rm -rf $(BUILD_DIR)

.PHONY: re
re: mrproper all

$(LOADER): $(LOADER_OBJECTS)
	@mkdir -p $(dir $@)
	$(LD) $(LOADER_LDFLAGS) $(LOADER_OBJECTS) -o $@

$(CHANTAGE): $(CHANTAGE_OBJECTS)
	@mkdir -p $(dir $@)
	$(LD) $(CHANTAGE_LDFLAGS) $(CHANTAGE_OBJECTS) -o $@

$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(LOADER_CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CHANTAGE_CFLAGS) -c $< -o $@
