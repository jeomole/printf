#include "main.h"
#include <stdio.h>

/**
 * _printf - produces output according to a format
 * @format: given string
 *
 * Return: The number of chars printed
 */
int _printf(const char *format, ...)
{
	unsigned int len = 0, i = 0, ibuf = 0;
	char *buffer;
	int (*handler)(va_list, char *, unsigned int);
	va_list args;

	va_start(args, format), buffer = malloc(sizeof(char) * 1024);
	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (!format[i])
		return (0);
	for (i = 0; format && format[i]; i++)
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '%')
				handl_buf(buffer, format[i], ibuf), len++;
			else if (format[i] == '\0')
			{
				print_buf(buffer, ibuf), free(buffer), va_end(args);
				return (-1);
			}
			else
			{
				handler = get_handl_func(format, i);
				if (handler == NULL)
					len++, i--, handl_buf(buffer, format[i], ibuf);
				else
					len += handler(args, buffer, ibuf);
			}
		}
		else
			handl_buf(buffer, format[i], ibuf), len++;
		for (ibuf = len; ibuf > 1024; ibuf -= 1024)
			;
	}
	print_buf(buffer, ibuf), free(buffer), va_end(args);
	return (len);
}
