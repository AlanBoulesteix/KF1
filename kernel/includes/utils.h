#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stddef.h>

bool is_digit(int c);
size_t strlen(const char *str);
char *strchr(const char *s, int c);

#endif