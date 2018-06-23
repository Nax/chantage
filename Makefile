CC				:= clang
TARGET			:= mipsel-none-elf
LD				:= $(TARGET)-ld

CFLAGS			:= --target=$(TARGET) -march=mips32r2 -mtune=mips32r2 -ffreestanding -nostdlib -Os
LDFLAGS			:= -T src/chantage/chantage.ld
OBJ_DIR			:= build
SRC_DIR			:= src/chantage
CHANTAGE_ELF	:= $(BUILD_DIR)/chantage.elf
CHANTAGE_BIN	:= $(BUILD_DIR)/chantage.bin


_SRCS	:= start.c
SRCS 	:= $(patsubst %,$(SRC_DIR)/%,$(_SRCS))
OBJS 	:= $(patsubst %,$(OBJ_DIR)/%,$(_SRCS:c=o))

.PHONY: all
all: $(CHANTAGE_BIN)


$(CHANTAGE_BIN): $(CHANTAGE_ELF)

$(CHANTAGE_ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
