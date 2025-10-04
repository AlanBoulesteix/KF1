#include "../includes/interrupt_handler.h"
#include "../includes/printk.h"

void interrupt_handler(stack_reg_t *reg)
{
    printk("int_no %d, error %d, ip %d, cs %d, flags %d, sp %d, ss %d", reg->int_no, reg->err_code, reg->ip, reg->cs, reg->flags, reg->sp, reg->ss);
}