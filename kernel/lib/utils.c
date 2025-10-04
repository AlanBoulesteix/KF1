#include "../includes/klib.h"

bool is_digit(uint32_t c)
{
	return (c >= '0' && c <= '9');
}

uint32_t strlen(const char *str)
{
	uint32_t len = 0;
	while (str[len])
		len++;
	return len;
}

char *strchr(const char *s, int c)
{
	unsigned int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}

int strcmp(const char *s1, const char *s2)
{
	size_t i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (unsigned char)s1[i] - (unsigned char)s2[i];
}