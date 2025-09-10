#ifndef NUMBERS_H
#define NUMBERS_H

#include <stdint.h>

int         putnbr(int n);
int         putnbr_unsigned(unsigned int n);
int         puthex(unsigned int n, const char *digits);
int         print_ptr(unsigned long long ptr);
int         print_bits_32(uint32_t value);
int         print_bits_64(uint64_t value);

#endif