#include "../../includes/printk.h"
#include "../../includes/numbers.h"
#include "../../includes/tty.h"
#include "../../includes/utils.h"

static int printk_arg(const char *fmt, int i, va_list ap)
{
    if (fmt[i + 1] == '%')
        return (terminal_write(&fmt[i + 1], 1));
    else if (fmt[i + 1] == 'c')
    {
        terminal_putchar(va_arg(ap, int));
        return 1;
    }
    else if (fmt[i + 1] == 's')
        return (terminal_writestring(va_arg(ap, char *)));
    else if (fmt[i + 1] == 'd' || fmt[i + 1] == 'i')
        return (putnbr(va_arg(ap, int)));
    else if (fmt[i + 1] == 'u')
        return (putnbr_unsigned(va_arg(ap, unsigned int)));
    else if (fmt[i + 1] == 'x' || fmt[i + 1] == 'X')
    {
        if (fmt[i + 1] == 'X')
            return (puthex(va_arg(ap, unsigned int), "0123456789ABCDEF"));
        else
            return (puthex(va_arg(ap, unsigned int), "0123456789abcdef"));
    }
    else if (fmt[i + 1] == 'p')
        return (print_ptr(va_arg(ap, unsigned long long)));
    else
        return (0);
}

int printk(const char *fmt, ...)
{
    va_list ap;
    int level = KERN_DEFAULT;
    int i = 0;
    int ret = 0;

    if (!fmt)
        return (-1);

    if (fmt[0] == '\001' && is_digit(fmt[1]))
    {
        level = fmt[1] - '0';
        fmt += 2;
    }

    if (level <= console_loglevel)
    {
        va_start(ap, fmt);
        while (fmt[i])
        {
            if (fmt[i] == '%' && strchr("cspdiuxX%", fmt[i + 1]))
            {
                ret += printk_arg(fmt, i, ap);
                i++;
            }
            else
                ret += terminal_write(&fmt[i], 1);
            i++;
        }
        va_end(ap);
    }
    return ret;
}