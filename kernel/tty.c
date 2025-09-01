#include "tty.h"

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t)uc | (uint16_t)color << 8;
}

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer = (uint16_t *)VGA_MEMORY;

static inline void outb(uint16_t port, uint8_t val)
{
	__asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	__asm__ volatile("inb %1, %0"
									 : "=a"(ret)
									 : "Nd"(port));
	return ret;
}

void update_cursor_pos(size_t x, size_t y)
{
	size_t pos = y * VGA_WIDTH + x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, pos & 0xFF);

	outb(0x3D4, 0x0E);
	outb(0x3D5, (pos >> 8) & 0xFF);
}

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void indent_terminal_rows()
{
	int y = -1;
	while (++y < VGA_HEIGHT - 1)
	{
		int x = -1;
		while (++x < VGA_WIDTH)
		{
			size_t index_dest = y * VGA_WIDTH + x;
			size_t index_src = (y + 1) * VGA_WIDTH + x;
			terminal_buffer[index_dest] = terminal_buffer[index_src];
		}
	}
	for (size_t x = 0; x < VGA_WIDTH; x++)
	{
		const size_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
	}
	terminal_row = VGA_HEIGHT - 1;
}

void terminal_putnewline()
{
	if (++terminal_row == VGA_HEIGHT)
		indant_terminal_rows();
	terminal_column = 0;
}

void terminal_putchar(char c)
{
	if (c == '\n')
		terminal_putnewline();
	else
	{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH)
		{
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				indant_terminal_rows();
		}
	}
	update_cursor_pos(terminal_column, terminal_row);
}

int terminal_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
	return size
}

int terminal_writestring(const char *data)
{
	int	data_len = strlen(data);

	terminal_write(data, len_data);

	return len_data;
}