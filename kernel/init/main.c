#include "../includes/tty.h"
#include "../includes/gdt.h"

void kernel_main(void)
{
	terminal_initialize();
	terminal_writestring("          @@@@@@@ @@@@@@@@@@@\n        @@@@@@@@  @@@@@@@@@@@\n      @@@@@@@@    @@@  @@@@@@\n     @@@@@@@          @@@@@@@\n   @@@@@@@          @@@@@@@@ \n @@@@@@@           @@@@@@@   \n @@@@@@@@@@@@@@@@ @@@@@@@  @@\n @@@@@@@@@@@@@@@@ @@@@@@@@@@@\n @@@@@@@@@@@@@@@@ @@@@@@@@@@@\n           @@@@@@            \n            @@@@@@            \n\n\n");
	dump_gdt();
}