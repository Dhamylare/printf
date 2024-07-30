#include "main.h"

unsigned int long_base(buffer_t *output, long int num, char *ptr,
		unsigned char flags, int d, int precise);
unsigned int unsigned_base(buffer_t *output,
		unsigned long int num, char *ptr,
		unsigned char flags, int d, int precise);

/**
 * long_base - Converts a signed value to an inputted base and stores
 *                 the result to a buffer contained in a struct.
 * @output: struct containing a character array.
 * @num: signed value to be converted.
 * @ptr: A pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @d: width modifier.
 * @precise: precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int long_base(buffer_t *output, long int num, char *ptr,
		unsigned char flags, int d, int precise)
{
	int s;
	char digit, pad = '0';
	unsigned int res = 1;

	for (s = 0; *(ptr + s);)
		s++;

	if (num >= s || num <= -s)
		res += long_base(output, num / s, ptr,
				flags, d - 1, precise - 1);

	else
	{
		for (; precise > 1; precise--, d--) /* Handles precision */
			res += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; d > 1; d--)
				res += _memcpy(output, &pad, 1);
		}
	}

	digit = ptr[(num < 0 ? -1 : 1) * (num % s)];
	_memcpy(output, &digit, 1);

	return (res);
}

/**
 * unsigned_base - Converts an unsigned long value to an inputted base and
 *                 stores the result to a buffer contained in a struct.
 * @output: A buffer_t struct containing a character array.
 * @num: An unsigned long to be converted.
 * @ptr: pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @d: width modifier.
 * @precise: precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int unsigned_base(buffer_t *output, unsigned long int num, char *ptr,
		unsigned char flags, int d, int precise)
{
	unsigned int s, res = 1;
	char digit, pad = '0', *prefix = "0x";

	for (s = 0; *(ptr + s);)
		s++;

	if (num >= s)
		res += unsigned_base(output, num / s, ptr,
				flags, d - 1, precise - 1);

	else
	{
		if (((flags >> 5) & 1) == 1) /* Prints a pointer address */
		{
			d -= 2;
			precise -= 2;
		}
		for (; precise > 1; precise--, d--) /* Handles precision */
			res += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handles width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; d > 1; d--)
				res += _memcpy(output, &pad, 1);
		}
		if (((flags >> 5) & 1) == 1) /* Print 0x for pointer with address */
			res += _memcpy(output, prefix, 2);
	}

	digit = ptr[(num % s)];
	_memcpy(output, &digit, 1);

	return (res);
}
