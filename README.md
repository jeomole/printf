_printf


DESCRIPTION:

A printf-like variable agument list function written in C that prints formatted output.

Function declaration prototype: int _printf(const char *format, ...);
Return value: It returns the number of characters printed (excluding the null byte used to end output to strings).

It writes output to stdout, the standard output stream.

HANDLED FORMAT SPECIFIERS

This function handles the following conversion specifiers:
d
i
c
s
%
