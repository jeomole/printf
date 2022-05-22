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
 *
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


/**
 * handl_bnr - prints decimal in binary
 *
 * @args: arguments
 * @buf: buffer
 * @ibuf: buffer index
 *
 * Return: number of chars printed
 */
int handl_bnr(va_list args, char *buf, unsigned int ibuf)
{
	int input, count, i, first_one, isneg = 0;
	char *binary;

	input = va_arg(args, int);
	if (input == 0)
	{
		ibuf = handl_buf(buf, '0', ibuf);
		return (1);
	}

	if (input < 0)
	{
		input = (input * -1) - 1;
		isneg = 1;
	}

	binary = malloc(sizeof(char) * (32 + 1));
	binary = fill_decimal_to_binary(binary, input, isneg, 32);
	first_one = 0;

	for (count = i = 0; binary[i]; i++)
	{
		if (first_one == 0 && binary[i] == '1')
			first_one = 1;
		if (first_one == 1)
		{
			ibuf = handl_buf(buf, binary[i], ibuf);
			count++;
		}
	}
	free(binary);
	return (count);
}


/**
 * handl_unint - prints an unsigned int
 *
 * @args: arguments
 * @buf: buffer
 * @ibuf: buffer index
 *
 * Return: number of chars printed
 */
int handl_unint(va_list args, char *buf, unsigned int ibuf)
{
	unsigned int input, d, i, count;

	input = va_arg(args, unsigned int);
	d = input, count = 1;
	while (d > 9)
		d /= 10, count *= 10;

	for (i = 0; count >= 1; count /= 10, i++)
		ibuf = handl_buf(buf, ((input / count) % 10) + '0', ibuf);

	return (i);
}

/**
 * handl_oct - prints decimal number in octal
 *
 * @args: arguments
 * @buf: buffer pointer
 * @ibuf: index for buffer
 *
 * Return: number of chars printed
 */
int handl_oct(va_list args, char *buf, unsigned int ibuf)
{
	int input, i, isneg, count, first_digit;
	char *octal, *binary;

	input = va_arg(args, int);
	isneg = 0;
	if (input == 0)
	{
		ibuf = handl_buf(buf, '0', ibuf);
		return (1);
	}
	if (input < 0)
	{
		input = (input * -1) - 1;
		isneg = 1;
	}
	binary = malloc(sizeof(char) * (32 + 1));
	binary = fill_decimal_to_binary(binary, input, isneg, 32);
	octal = malloc(sizeof(char) * (11 + 1));
	octal = fill_binary_to_oct(binary, octal);

	for (first_digit = i = count = 0; octal[i]; i++)
	{
		if (octal[i] != '0' && first_digit == 0)
			first_digit = 1;
		if (first_digit)
		{
			ibuf = handl_buf(buf, octal[i], ibuf);
			count++;
		}
	}
	free(binary);
	free(octal);
	return (count);
}

/**
 * handl_hex - handles %x format specifier
 *
 * @args: arguments
 * @buf: buffer
 * @ibuf: index for buffer pointer
 *
 * Return: number of chars printed
 */
int handl_hex(va_list args, char *buf, unsigned int ibuf)
{
	int int_input, i, isnegative, count, first_digit;
	char *hexadecimal, *binary;

	int_input = va_arg(args, int);
	isnegative = 0;
	if (int_input == 0)
	{
		ibuf = handl_buf(buf, '0', ibuf);
		return (1);
	}
	if (int_input < 0)
	{
		int_input = (int_input * -1) - 1;
		isnegative = 1;
	}
	binary = malloc(sizeof(char) * (32 + 1));
	binary = fill_decimal_to_binary(binary, int_input, isnegative, 32);
	hexadecimal = malloc(sizeof(char) * (8 + 1));
	hexadecimal = fill_binary_to_hex(binary, hexadecimal, 0, 8);
	for (first_digit = i = count = 0; hexadecimal[i]; i++)
	{
		if (hexadecimal[i] != '0' && first_digit == 0)
			first_digit = 1;
		if (first_digit)
		{
			ibuf = handl_buf(buf, hexadecimal[i], ibuf);
			count++;
		}
	}
	free(binary);
	free(hexadecimal);
	return (count);
}

/**
 * handl_addr - prints the address of an input variable
 * @arguments: input address.
 * @buf: buffer pointer.
 * @ibuf: index for buffer pointer
 *
 * Return: number of chars printed.
 */
int handl_addr(va_list arguments, char *buf, unsigned int ibuf)
{
	void *add;
	long int int_input;
	int i, count, first_digit, isnegative;
	char *hexadecimal, *binary;
	char nill[] = "(nil)";

	add = (va_arg(arguments, void *));
	if (add == NULL)
	{
		for (i = 0; nill[i]; i++)
			ibuf = handl_buf(buf, nill[i], ibuf);
		return (5);
	}
	int_input = (intptr_t)add;
	isnegative = 0;
	if (int_input < 0)
	{
		int_input = (int_input * -1) - 1;
		isnegative = 1;
	}
	binary = malloc(sizeof(char) * (64 + 1));
	binary = fill_decimal_to_binary(binary, int_input, isnegative, 64);
	hexadecimal = malloc(sizeof(char) * (16 + 1));
	hexadecimal = fill_binary_to_hex(binary, hexadecimal, 0, 16);
	ibuf = handl_buf(buf, '0', ibuf);
	ibuf = handl_buf(buf, 'x', ibuf);
	for (first_digit = i = count = 0; hexadecimal[i]; i++)
	{
		if (hexadecimal[i] != '0' && first_digit == 0)
			first_digit = 1;
		if (first_digit)
		{
			ibuf = handl_buf(buf, hexadecimal[i], ibuf);
			count++;
		}
	}
	free(binary);
	free(hexadecimal);
	return (count + 2);
}

