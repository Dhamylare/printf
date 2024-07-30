#include "main.h"
unsigned int print_di(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_b(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_u(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_o(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
/**
 * print_di - prints signed integers
 * @ap: variable arguments
 * @flags: flag modifiers
 * @d: width modifier
 * @precise: precision modifier
 * @len: length modifier
 * @output: buffer
 * Return: number of bytes stored
 */
unsigned int print_di(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	long int k, copy;
	unsigned int res = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (len == LONG)
		k = va_arg(ap, long int);
	else
		k = va_arg(ap, int);
	if (len == SHORT)
		k = (short)k;
	if (SPACE_FLAG == 1 && k >= 0)
		res += _memcpy(output, &space, 1);
	if (precise <= 0 && NEG_FLAG == 0)
	{
		if (k == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (k < 0) ? -k : k; copy > 0; copy /= 10)
				count++;
		}
		count += (k == 0) ? 1 : 0;
		count += (k < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && k >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && k >= 0) ? 1 : 0;
		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && k >= 0)
			res += _memcpy(output, &plus, 1);
		if (ZERO_FLAG == 1 && k < 0)
			res += _memcpy(output, &neg, 1);
		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (d -= count; d > 0; d--)
			res += _memcpy(output, &pad, 1);
	}
	if (ZERO_FLAG == 0 && k < 0)
		res += _memcpy(output, &neg, 1);
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && k >= 0))
		res += _memcpy(output, &plus, 1);
	if (!(k == 0 && precise == 0))
		res += long_base(output, k, "0123456789",
				flags, 0, precise);
	res += print_neg_width(output, res, flags, d);
	return (res);
}
/**
 * print_b - prints binary
 * @ap: variable argument
 * @flags: flag modifiers
 * @d: width modifier
 * @precise: precision modifier.
 * @len: length modifier.
 * @output: buffer
 * Return: number of bytes stored
 */
unsigned int print_b(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	unsigned int num;

	num = va_arg(ap, unsigned int);
	(void)len;
	return (unsigned_base(output, num, "01", flags, d, precise));
}
/**
 * print_o - prints octal numbers
 * @ap: variable argument
 * @flags: flag modifiers.
 * @d: width modifier.
 * @precise: precision modifier.
 * @len: length modifier.
 * @output: buffer
 * Return: number of bytes stored
 */
unsigned int print_o(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	unsigned long int num;
	unsigned int res = 0;
	char zero = '0';

	if (len == LONG)
		num = va_arg(ap, unsigned long int);
	else
		num = va_arg(ap, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;
	if (HASH_FLAG == 1 && num != 0)
		res += _memcpy(output, &zero, 1);
	if (!(num == 0 && precise == 0))
		res += unsigned_base(output, num, "01234567",
				flags, d, precise);
	res += print_neg_width(output, res, flags, d);
	return (res);
}
/**
 * print_u - prints an unsigned int
 * @ap: variable argument
 * @flags: flag modifiers
 * @d: width modifier
 * @precise: precision modifier
 * @len: length modifier.
 * @output: buffer
 * Return: number of bytes stored
 */
unsigned int print_u(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	unsigned long int num;
	unsigned int res = 0;

	if (len == LONG)
		num = va_arg(ap, unsigned long int);
	else
		num = va_arg(ap, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (!(num == 0 && precise == 0))
		res += unsigned_base(output, num, "0123456789",
				flags, d, precise);

	res += print_neg_width(output, res, flags, d);

	return (res);
}
