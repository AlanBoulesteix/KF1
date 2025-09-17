#include "../includes/tty.h"

void kernel_main(void)
{
	terminal_initialize();
	terminal_writestring("          [red]@@@@@@@ @@@@@@@@@@@[reset]\n        [cyan_light]@@@@@@@@  @@@@@@@@@@@[reset]\n      [blue]@@@@@@@@    @@@  @@@@@@[reset]\n     [green]@@@@@@@          @@@@@@@[reset]\n   [magenta]@@@@@@@          @@@@@@@@ [reset]\n [brown]@@@@@@@           @@@@@@@   [reset]\n [brown_light]@@@@@@@@@@@@@@@@ @@@@@@@  @@[reset]\n [green_light]@@@@@@@@@@@@@@@@ @@@@@@@@@@@[reset]\n [grey_dark]@@@@@@@@@@@@@@@@ @@@@@@@@@@@[reset]\n[white]           @@@@@@            [reset]\n[red_light]            @@@@@@            \n\n\n");
}