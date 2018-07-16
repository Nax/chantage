TARGET				:= mips-unknown-elf
AR 					:= $(TARGET)-ar
CC					:= $(TARGET)-gcc
LD					:= $(TARGET)-ld
PSP_PRXGEN			:= psp-prxgen

BUILD_DIR			:= build
CFLAGS				:= -EL -mabi=eabi -march=mips2 -mtune=mips2 -Iinclude -ffreestanding -nostdlib -Os -MMD

PRX_LOADER 			:= $(BUILD_DIR)/lib/libprxloader.a
PRX_LOADER_SOURCES	:= $(shell find src/prx_loader -name '*.c')
PRX_LOADER_OBJECTS	:= $(PRX_LOADER_SOURCES:%=$(BUILD_DIR)/%.o)

LOADER				:= $(BUILD_DIR)/chantage_loader.bin
LOADER_SOURCES		:= $(shell find src/chantage_loader -name '*.c')
LOADER_OBJECTS		:= $(LOADER_SOURCES:%=$(BUILD_DIR)/%.o)
LOADER_LDFLAGS		:= -T src/flat_binary.ld

CHANTAGE			:= $(BUILD_DIR)/chantage.prx
CHANTAGE_ELF		:= $(BUILD_DIR)/chantage.elf
CHANTAGE_SOURCES	:= $(shell find src/chantage -name '*.c')
CHANTAGE_OBJECTS	:= $(CHANTAGE_SOURCES:%=$(BUILD_DIR)/%.o)
CHANTAGE_LDFLAGS	:= -EL -q -T src/elf.ld

SLOWDOWN			:= $(BUILD_DIR)/mods/slowdown_fix.prx
SLOWDOWN_ELF		:= $(BUILD_DIR)/mods/slowdown_fix.elf
SLOWDOWN_SOURCES	:= src/slowdown.c
SLOWDOWN_OBJECTS	:= $(BUILD_DIR)/src/slowdown.c.o
SLOWDOWN_LDFLAGS	:= $(CHANTAGE_LDFLAGS)

DIST_DIR			:= dist
DIST				:= $(DIST_DIR)/chantage.zip
DIST_TMP 			:= $(DIST_DIR)/tmp
DIST_PSPDIR			:= $(DIST_TMP)/PSP/GAME/ULUS10297
DIST_MODSDIR		:= $(DIST_PSPDIR)/mods

.PHONY: all
all: $(LOADER) $(CHANTAGE) $(SLOWDOWN)

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

$(PRX_LOADER): $(PRX_LOADER_OBJECTS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $(PRX_LOADER_OBJECTS)

$(LOADER): $(LOADER_OBJECTS) $(PRX_LOADER)
	@mkdir -p $(dir $@)
	$(LD) $(LOADER_LDFLAGS) $(LOADER_OBJECTS) -L$(BUILD_DIR)/lib -lprxloader -o $@

$(CHANTAGE): $(CHANTAGE_ELF)
	@mkdir -p $(dir $@)
	$(PSP_PRXGEN) $< $@

$(CHANTAGE_ELF): $(CHANTAGE_OBJECTS) $(PRX_LOADER)
	@mkdir -p $(dir $@)
	$(LD) $(CHANTAGE_LDFLAGS) $(CHANTAGE_OBJECTS) -L$(BUILD_DIR)/lib -lprxloader -o $@

$(SLOWDOWN): $(SLOWDOWN_ELF)
	@mkdir -p $(dir $@)
	$(PSP_PRXGEN) $< $@

$(SLOWDOWN_ELF): $(SLOWDOWN_OBJECTS)
	@mkdir -p $(dir $@)
	$(LD) $(SLOWDOWN_LDFLAGS) $(SLOWDOWN_OBJECTS) -o $@


$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
