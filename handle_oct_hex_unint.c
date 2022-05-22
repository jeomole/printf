#include "main.h"

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
