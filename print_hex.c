#include "main.h"

unsigned int printt_x(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_X(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);

/**
 * print_x - hexadecimal in small letters
 * @ap: variable argument
 * @flags: flag modifiers.
 * @d: width modifier.
 * @precise: precision modifier.
 * @len: length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: number of bytes stored
 */
unsigned int print_x(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	unsigned long int num;
	unsigned int res = 0;
	char *prefix = "0x";

	if (len == LONG)
		num = va_arg(ap, unsigned long int);
	else
		num = va_arg(ap, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		res += _memcpy(output, prefix, 2);

	if (!(num == 0 && precise == 0))
		res += unsigned_base(output, num, "0123456789abcdef",
				flags, d, precise);

	res += print_neg_width(output, res, flags, d);

	return (res);
}

/**
 * print_X - prints hexadecimal in caps using
 *
 * @ap: variable argument
 * @flags: flag modifiers.
 * @d: width modifier.
 * @precise: precision modifier.
 * @len: length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_X(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	unsigned long int num;
	unsigned int res = 0;
	char *prefix = "0X";

	if (len == LONG)
		num = va_arg(ap, unsigned long);
	else
		num = va_arg(ap, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		res += _memcpy(output, prefix, 2);

	if (!(num == 0 && precise == 0))
		res += unsigned_base(output, num, "0123456789ABCDEF",
				flags, d, precise);

	res += print_neg_width(output, res, flags, d);

	return (res);
}
