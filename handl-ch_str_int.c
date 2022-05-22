#include "main.h"

/**
 * handl_str - writes the string to stdout
 *
 * @args: arguments
 * @buf: buffer pointer
 * @ibuf: index for buffer pointer
 *
 * Return: length of string added
 */
int handl_str(va_list args, char *buf, unsigned int ibuf)
{
	char *str;
	unsigned int i;
	char nil[] = "(nil)";

	str = va_arg(args, char *);
	if (!str)
	{
		for (i = 0; nil[i]; i++)
			ibuf = handl_buf(buf, nil[i], ibuf);
		return (5);
	}
	for (i = 0; str[i]; i++)
		ibuf = handl_buf(buf, str[i], ibuf);
	return (i);
}

/**
 * handl_int - prints an integer
 *
 * @args: arguments
 * @buf: buffer pointer
 * @ibuf: index for the buffer
 *
 * Return: number of chars printed
 */
int handl_int(va_list args, char *buf, unsigned int ibuf)
{
	int input;
	unsigned int abs, count, i, d, isneg;

	input = va_arg(args, int);
	isneg = 0;
	if (input < 0)
	{
		abs = input * -1;
		ibuf = handl_buf(buf, '-', ibuf);
		isneg = 1;
	}
	else
	{
		abs = input;
	}

	d = abs, count = 1;
	while (d > 9)
	{
		d /= 10;
		count *= 10;
	}

	for (i = 0; count >= 1; count /= 10, i++)
		ibuf = handl_buf(buf, ((abs / count) % 10) + '0', ibuf);

	return (i + isneg);
}

/**
 * handl_ch - handles writing character to stdout
 *
 * @args: arguments
 * @buf: buffer pointer
 * @bufferIndex: index for buffer pointer
 *
 * Return: length of char addition
 */
int handl_ch(va_list args, char *buf, unsigned int bufferIndex)
{
	char c;

	c = va_arg(args, int);
	handl_buf(buf, c, bufferIndex);

	return (1);
}
