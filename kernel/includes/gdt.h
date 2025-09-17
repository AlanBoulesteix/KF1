#ifndef GDT_H

#define GDT_H

#include <stdint.h>

// Each define here is for a specific flag in the descriptor.
// Refer to the intel documentation for a description of what each one does.
#define SEG_DESCTYPE(x)  ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)      ((x) << 0x07) // Present
#define SEG_SAVL(x)      ((x) << 0x0C) // Available for system use
#define SEG_LONG(x)      ((x) << 0x0D) // Long mode
#define SEG_SIZE(x)      ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)      ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)     (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)

// 1st bit: executable bit: 0=data ; 1=code
// 2nd bit: direction bit if data: 0=segment grows up ; 1= segment gros down
//          conforming bit if code: 0=executable only from ring set in SEG_PRIV ; 1=executable from ring set in SEG_PRIV or lower
// 3rd bit: data: 0=write access not allowed ; 1=write access allowed ; read access always allowed
//          code: 0=read access not allowed ; 1=read access allowed ; write access never allowed
// 4th bit: access bit
#define SEG_DATA_RD        0x00 // Read-Only b0000
#define SEG_DATA_RDA       0x01 // Read-Only, accessed b0001
#define SEG_DATA_RDWR      0x02 // Read/Write b0010
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed b0011
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down b0100
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed b0101
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down b0110
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed b0111
#define SEG_CODE_EX        0x08 // Execute-Only b1000
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed b1001
#define SEG_CODE_EXRD      0x0A // Execute/Read b1010
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed b1011
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming b1100
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed b1101
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming b1110
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed b1111
 
#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR
 
#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR

struct gdt_register {
    uint16_t    limit;
    uint32_t    base;
}__attribute__((packed));

extern struct gdt_register gdtr;  

uint64_t    create_descriptor(uint32_t base, uint32_t limit, uint16_t flag);
void        init_gdt(void);
void        dump_gdt(void);

#endif