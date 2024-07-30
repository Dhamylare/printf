#include "main.h"

unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int d);
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int d, int precise, int s);
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int d);

/**
 * print_width - Stores leading spaces for a width modifier
 * @output: buffer
 * @printed: number of characters already printed
 * @flags: flag modifiers
 * @d: width modifier
 *
 * Return: number of bytes
 */
unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int d)
{
	unsigned int res = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		for (d -= printed; d > 0;)
			res += _memcpy(output, &width, 1);
	}

	return (res);
}

/**
 * print_string_width - Stores leading spaces
 * @output: buffer
 * @flags: flag modifiers
 * @d: width modifier
 * @precise: precision modifier
 * @s: size of the string
 * Return: number of bytes stored
 */
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int d, int precise, int s)
{
	unsigned int res = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		d -= (precise == -1) ? s : precise;
		for (; d > 0; d--)
			res += _memcpy(output, &width, 1);
	}

	return (res);
}

/**
 * print_neg_width - Stores trailing spaces for a negative flag
 * @output: buffer
 * @printed: number of bytes already stored to output
 * @flags: flag modifiers
 * @d: width modifier
 * Return: number of bytes stored
 */
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int d)
{
	unsigned int res = 0;
	char width = ' ';

	if (NEG_FLAG == 1)
	{
		for (d -= printed; d > 0; d--)
			res += _memcpy(output, &width, 1);
	}

	return (res);
}
