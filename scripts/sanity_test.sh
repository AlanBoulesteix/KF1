if grub-file --is-x86-multiboot build/iso/boot/kernel.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi