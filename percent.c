#include "main.h"

unsigned int print_c(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_percent(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_p(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);

/**
 * print_char - prints an argument as char and
 *             stores it to a buffer contained in a struct.
 * @ap: argument to be converted.
 * @flags: Flag modifiers.
 * @d: width modifier.
 * @precise: precision modifier.
 * @len: length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: number of bytes stored
 */
unsigned int print_c(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	char c;
	unsigned int res = 0;

	(void)precise;
	(void)len;

	c = va_arg(ap, int);

	res += print_width(output, res, flags, d);
	res += _memcpy(output, &c, 1);
	res += print_neg_width(output, res, flags, d);

	return (res);
}

/**
 * print_percent - prints a percent sign
 * @ap: argument to be converted.
 * @flags: flag modifiers.
 * @d: modifier.
 * @precise: precision modifier.
 * @len: length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: bytes stored (always 1).
 */
unsigned int print_percent(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	char percent = '%';
	unsigned int res = 0;

	(void)ap;
	(void)precise;
	(void)len;

	res += print_width(output, res, flags, d);
	res += _memcpy(output, &percent, 1);
	res += print_neg_width(output, res, flags, d);

	return (res);
}

/**
 * print_pointer - prints the address of an argument in hex and
 *             stores it to a buffer contained in a struct.
 * @ap: argument to be printed.
 * @flags: flag modifiers.
 * @d: width modifier.
 * @precise: precision modifier.
 * @len: length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_p(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int add;
	unsigned int res = 0;

	(void)len;

	add = va_arg(ap, unsigned long int);
	if (add == '\0')
		return (_memcpy(output, null, 5));

	flags |= 32;
	res += unsigned_base(output, add, "0123456789abcdef",
			flags, d, precise);
	res += print_neg_width(output, res, flags, d);

	return (res);
}
