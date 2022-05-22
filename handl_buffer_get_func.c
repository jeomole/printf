#include "main.h"

/**
 * handl_buf - handles buffer concatenation
 *
 * @buf: buffer pointer
 * @c: character to concatenate
 * @ibuf: index of buffer pointer
 *
 * Return: index of buffer pointer
 */
unsigned int handl_buf(char *buf, char c, unsigned int ibuf)
{
	if (ibuf == 1024)
	{
		print_buf(buf, ibuf);
		ibuf = 0;
	}
	buf[ibuf] = c;
	ibuf++;
	return (ibuf);
}

/**
 * print_buf - prints the buffer of currently stored up bytes of characters
 * @buf: a pointer to the buffer
 * @n: number of bytes to print
 * Return: number of printed bytes
 */
int print_buf(char *buf, unsigned int n)
{
	return (write(1, buf, n));
}

/**
 * get_handl_func - map specifier with appropriate function
 * @s: specifier
 * @index: index for argument identifier
 *
 * Return: pointer to function
 */
int (*get_handl_func(const char *s, int index))(va_list, char *, unsigned int)
{
	handl_t hn[] = {
		{"c", handl_ch},
		{"s", handl_str},
		{"i", handl_int},
		{"d", handl_int},
		{NULL, NULL},
	};
	int i = 0;

	for (; hn[i].specifier; i++)
		if (s[index] == hn[i].specifier[0])
			return (hn[i].f);

	return (NULL);
}
