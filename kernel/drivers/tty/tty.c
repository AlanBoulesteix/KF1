#include "../../includes/tty.h"
#include "../../includes/io.h"
#include "../../includes/utils.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer = (uint16_t *)VGA_MEMORY;
struct color_map colors[] = {
		{"black", VGA_COLOR_BLACK},
		{"blue", VGA_COLOR_BLUE},
		{"green", VGA_COLOR_GREEN},
		{"cyan", VGA_COLOR_CYAN},
		{"red", VGA_COLOR_RED},
		{"magenta", VGA_COLOR_MAGENTA},
		{"brown", VGA_COLOR_BROWN},
		{"grey_light", VGA_COLOR_LIGHT_GREY},
		{"grey_dark", VGA_COLOR_DARK_GREY},
		{"blue_light", VGA_COLOR_LIGHT_BLUE},
		{"green_light", VGA_COLOR_LIGHT_GREEN},
		{"cyan_light", VGA_COLOR_LIGHT_CYAN},
		{"red_light", VGA_COLOR_LIGHT_RED},
		{"magenta_light", VGA_COLOR_LIGHT_MAGENTA},
		{"brown_light", VGA_COLOR_LIGHT_BROWN},
		{"white", VGA_COLOR_WHITE},
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t)uc | (uint16_t)color << 8;
}

void update_cursor_pos(size_t x, size_t y)
{
	size_t pos = y * VGA_WIDTH + x;
	outb(VGA_CONTROLER_SELECT, VGA_CURSOR_LOW);
	outb(VGA_CONTROLER_SET, pos & 0xFF);

	outb(VGA_CONTROLER_SELECT, VGA_CURSOR_HIGH);
	outb(VGA_CONTROLER_SET, (pos >> 8) & 0xFF);
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
		indent_terminal_rows();
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
				indent_terminal_rows();
		}
	}
	update_cursor_pos(terminal_column, terminal_row);
}

static bool read_tag(char tag[32])
{
	if (strcmp(tag, "reset") == 0)
	{
		terminal_setcolor(VGA_COLOR_LIGHT_GREY);
		return 1;
	}
	for (size_t i = 0; i < 16; i++)
	{
		if (strcmp(tag, colors[i].name) == 0)
		{
			terminal_setcolor(colors[i].vga);
			return 1;
		}
	}
	return 0;
}

int terminal_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == '[')
		{
			char tag[32];
			size_t j = 0;

			i++;
			while (data[i + j] && data[i + j] != ']' && j < 31)
			{
				tag[j] = data[i + j];
				j++;
			}
			tag[j] = '\0';
			if (data[i + j] == ']')
			{
				if (read_tag(tag))
					i += j + 1;
				else
					i--;
			}
			else
				i--;
		}
		terminal_putchar(data[i]);
	}
	return size;
}

int terminal_writestring(const char *data)
{
	int len_data = strlen(data);

	terminal_write(data, len_data);

	return len_data;
}