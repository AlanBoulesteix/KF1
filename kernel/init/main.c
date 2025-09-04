#include "../includes/tty.h"

void kernel_main(void)
{
	terminal_initialize();
	terminal_writestring("          [red]@@@@@@@ @@@@@@@@@@@[reset]\n        [yellow]@@@@@@@@  @@@@@@@@@@@[reset]\n      [blue]@@@@@@@@    @@@  @@@@@@[reset]\n     [green]@@@@@@@          @@@@@@@[reset]\n   [magenta]@@@@@@@          @@@@@@@@ [reset]\n [brown]@@@@@@@           @@@@@@@   [reset]\n @@@@@@@@@@@@@@@@ @@@@@@@  @@[reset]\n @@@@@@@@@@@@@@@@ @@@@@@@@@@@[reset]\n @@@@@@@@@@@@@@@@ @@@@@@@@@@@[reset]\n           @@@@@@            [reset]\n            @@@@@@            [reset]\n[reset]\n[reset]\n");
}