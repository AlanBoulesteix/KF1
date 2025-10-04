#include "../includes/io.h"
#include "../includes/isr.h"
#include "../includes/printk.h"

const char scancode_to_ascii[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

char get_ascii_char(uint8_t scancode)
{
    if (scancode >= sizeof(scancode_to_ascii))
    {
        return 0;
    }
    return scancode_to_ascii[scancode];
}

void interrupt_handler(void)
{
    uint8_t scancode = inb(0x60);

    // Ignorer les break codes (bit 7 = 1)
    if (scancode & 0x80)
    {
        PIC_sendEOI(1);
        return;
    }

    // Convertir en ASCII
    char c = get_ascii_char(scancode);

    // Si c'est un caractère imprimable, l'afficher
    if (c != 0)
    {
        printk("%c", c);
    }

    PIC_sendEOI(1);
}