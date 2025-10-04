#pragma once

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef unsigned long long   uint64_t;
typedef uint8_t         bool;
typedef unsigned long   uintptr_t;
typedef long            size_t;

typedef struct stack_reg {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t ip, cs, flags, sp, ss;
} stack_reg_t;

#define true    1
#define false   0

#define NULL (void*)0

bool        is_digit(uint32_t c);
uint32_t    strlen(const char *str);
char        *strchr(const char *s, int c);
int         strcmp(const char *s1, const char *s2);