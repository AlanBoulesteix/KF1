#include "../../includes/numbers.h"
#include "../../includes/tty.h"

static int print_unsigned(unsigned int value, int base, const char *digits) {
    char buffer[10];
    int i = 0;
    int len = 0;
    
    if (value == 0) {
        terminal_putchar('0');
        return 1;
    }
    
    while (value) {
        buffer[i++] = digits[value % base];
        value /= base;
    }
    
    len = i;
    
    while (i > 0) {
        terminal_putchar(buffer[--i]);
    }
    
    return len;
}

static int print_unsigned_long_long(unsigned long long value, int base, const char *digits) {
    char buffer[20];
    int i = 0;
    int len = 0;
    
    if (value == 0) {
        terminal_putchar('0');
        return 1;
    }
    
    while (value) {
        buffer[i++] = digits[value % base];
        value /= base;
    }
    
    len = i;
    
    while (i > 0) {
        terminal_putchar(buffer[--i]);
    }
    
    return len;
}

int putnbr(int n) {
    int len = 0;
    
    if (n < 0) {
        terminal_putchar('-');
        len++;
        len += print_unsigned((unsigned int)(-n), 10, "0123456789");
    } else {
        len = print_unsigned((unsigned int)n, 10, "0123456789");
    }
    
    return len;
}

int putnbr_unsigned(unsigned int n) {
	
	return print_unsigned(n, 10, "0123456789");
}

int puthex(unsigned int n, const char *digits) {
	terminal_writestring("0x");
    return print_unsigned(n, 16, digits) + 2;
}

int print_ptr(unsigned long long ptr) {
    if (ptr == 0) {
        return terminal_writestring("0x0");
    }

	return print_unsigned_long_long(ptr, 10, "0123456789");
}