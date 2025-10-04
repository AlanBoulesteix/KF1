#include "../includes/io.h"
#include "../includes/isr.h"
#include "../includes/printk.h"

void interrupt_handler(void)
{
    printk("COUCOU");
    uint8_t scancode = inb(0x60); // lit la touche pressée
    printk("Key pressed: %x\n", scancode);
    PIC_sendEOI(1); // dit au PIC qu'on a fini
}
