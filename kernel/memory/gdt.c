 #include "../includes/gdt.h" 
#include "../includes/printk.h" 

uint64_t            descriptors[5];
struct gdt_register gdtr;

uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag) {
    uint64_t descriptor = 0;
 
    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;
 
    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0

    return descriptor;
}
 
void init_gdt(void) {
    gdtr.limit = sizeof(descriptors) - 1;
    gdtr.base = (uint32_t)&descriptors;

    descriptors[0] = create_descriptor(0, 0, 0);
    descriptors[1] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    descriptors[2] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    descriptors[3] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    descriptors[4] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3));

}

void dump_gdt(void) {
    printk("GDT at: \n%b\n", (uint32_t)&descriptors);

    for (int i = 0; i < 5; i++) {
        printk("Descriptor %d: \n%B\n", i, (uint64_t)descriptors[i]);
    }
    // uint64_t des = 0;
    // uint32_t base = 0;
    // uint32_t limit = 0x000FFFFF;
    // uint16_t flag = GDT_CODE_PL0;
 
    // // Create the high 32 bit segment
    // des  =  limit       & 0x000F0000;         // set limit bits 19:16
    // printk("1:\n%B\n", des);
    // des |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    // printk("2:\n%B\n", des);
    // des |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    // printk("3:\n%B\n", des);
    // des |=  base        & 0xFF000000;         // set base bits 31:24
    // printk("4:\n%B\n", des);
    
    // // Shift by 32 to allow for low part of segment
    // des <<= 32;
    // printk("5:\n%B\n", des);
    
    // // Create the low 32 bit segment
    // des |= base  << 16;                       // set base bits 15:0
    // printk("6:\n%B\n", des);
    // des |= limit  & 0x0000FFFF;               // set limit bits 15:0
    // printk("7:\n%B\n", des);
}
