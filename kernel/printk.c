#include <stdarg.h>
#include "helper.h"

int    printk(const char* fmt, ...){
    va_list ap;
    int     level = KERN_DEFAULT;
    int     i = 0;
    int     ret = 0;

    if (!fmt)
        return (-1);
    
    if (fmt[0] == KERN_SOH && isdigit(fmt[1])) {
        level = fmt[1] - 0;
        fmt += 2;
    }

    if (level <= console_loglevel) {
        va_start(ap, fmt);
        while (fmt[i])
        {
            if (fmt[i] == '%' && ft_strchr("cspdiuxX%", fmt[i + 1]))
            {
                ret += printk_arg(fmt, i, ap);
                i++;
            }
            else
                ret += terminal_putchar(fmt[i]);
            i++;
        }
        va_end(ap);
    }
}

int	printk_arg(const char *fmt, int i, va_list ap)
{
	if (fmt[i + 1] == '%')
		return (terminal_putchar(fmt[i + 1]));
	else if (fmt[i + 1] == 'c')
		return (terminal_putchar(va_arg(ap, int)));
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