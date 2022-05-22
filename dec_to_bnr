#include "main.h"

/**
 * fill_decimal_to_binary - decimal to binary
 *
 * @binary: pointer to output
 * @input: input decimal
 * @isneg: is negative
 * @limit: size of binary
 *
 * Return: pointer to output
 */
char *fill_decimal_to_binary(char *binary, long int input
		, int isneg, int limit)
{
	int i;

	for (i = 0; i < limit; i++)
		binary[i] = '0';
	binary[limit] = '\0';

	for (i = limit - 1; input > 1; i--)
	{
		if (input == 2)
			binary[i] = '0';
		else
			binary[i] = (input % 2) + '0';
		input /= 2;
	}

	if (input != 0)
		binary[i] = '1';

	if (isneg)
	{
		for (i = 0; binary[i]; i++)
			if (binary[i] == '0')
				binary[i] = '1';
			else
				binary[i] = '0';
	}
	return (binary);
}
