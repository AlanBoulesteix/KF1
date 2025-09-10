TARGET			:= kfs.iso
ARCH			:= i386
IMAGE_NAME		:= kfs-buildenv

BUILD_DIR		:= build
BOOT_SRC		:= boot
KERNEL_SRC		:= kernel
KERNEL_BUILD	:= $(BUILD_DIR)/kernel
KERNEL_INC		:= $(KERNEL_SRC)/includes

# Files
LINKER			:= $(BOOT_SRC)/linker.ld
ASM_SRCS		:= $(shell find . -name "*.s")
ASM_OBJS		:= $(patsubst ./%.s,$(BUILD_DIR)/%.o,$(ASM_SRCS))
KERNEL_BIN		:= $(BUILD_DIR)/kernel.bin
ISO_DIR			:= $(BUILD_DIR)/iso
GRUB_CFG		:= $(BOOT_SRC)/grub.cfg

# Get all C source files recursively
KERNEL_SRCS		:= $(shell find $(KERNEL_SRC) -name "*.c")
KERNEL_OBJS		:= $(patsubst $(KERNEL_SRC)/%.c,$(KERNEL_BUILD)/%.o,$(KERNEL_SRCS))
DEPS					:= $(KERNEL_OBJS:%.o=%.d)

# Compiler settings
CC				:= $(ARCH)-elf-gcc
CFLAGS			:= -std=gnu99 -ffreestanding -O2 -g -Wall -Wextra -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs -MMD
LDFLAGS			:= -T $(LINKER) -nostdlib -nodefaultlibs
ASM				:= $(ARCH)-elf-as

build:
	docker build -f build-env/kernel.Dockerfile -t $(IMAGE_NAME) .
	docker run --rm -v .:/workspace kfs-buildenv make $(TARGET)

# Create the iso file with grub installed
$(TARGET): $(KERNEL_BIN)
	@mkdir -p $(ISO_DIR)/boot/grub
	cp $(GRUB_CFG) $(ISO_DIR)/boot/grub/grub.cfg
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/kernel.bin
	grub-mkrescue -o $(TARGET) $(ISO_DIR)

# Link object files to create the kernel binary
$(KERNEL_BIN): $(ASM_OBJS) $(KERNEL_OBJS) $(KERNEL_INC)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $(ASM_OBJS) $(KERNEL_OBJS) -lgcc

# Assemble each asm file
$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(ASM) $< -o $@

# Compile kernel c files
$(KERNEL_BUILD)/%.o: $(KERNEL_SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(KERNEL_INC)

run:
	kvm $(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(KERNEL_BIN)

fclean: clean
	rm -f $(TARGET)

dclean: 
	docker rmi -f $(IMAGE_NAME) 2>/dev/null || true

re: fclean dclean build

.PHONY: build run clean fclean dclean re

-include $(DEPS)