#ifndef HELPER_H
#   define HELPER_H

#include <stdbool.h>
#include <stddef.h>

bool    is_digit(int c);
size_t  strlen(const char *str);
int putnbr(int n);
int putnbr_unsigned(unsigned int n);
int puthex(unsigned int n, const char *digits);

#endif