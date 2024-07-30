#include "main.h"

unsigned int print_s(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_S(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_r(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_R(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);

/**
 * convert_s - prints a string
 *
 * @ap: variable argument
 * @flags: flag modifiers
 * @d: width modifier.
 * @precise: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct that stores character array.
 *
 * Return: number of bytes stored
 */
unsigned int print_s(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	char *str, *null = "(null)";
	int s;
	unsigned int res = 0;

	(void)flags;
	(void)len;

	str = va_arg(ap, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (s = 0; *(str + s);)
		s++;

	res += print_string_width(output, flags, d, precise, s);

	precise = (precise == -1) ? s : precise;
	while (*str != '\0' && precise > 0)
	{
		res += _memcpy(output, str, 1);
		precise--;
		str++;
	}

	res += print_neg_width(output, res, flags, d);

	return (res);
}

/**
 * print_S - prints special characters
 *
 * @ap: variable argument
 * @flags: flag modifiers.
 * @d: width modifier.
 * @precise: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored.
 *
 * Description: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 */
unsigned int print_S(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int s, index;
	unsigned int res = 0;

	(void)len;
	str = va_arg(ap, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (s = 0; str[s];)
		s++;

	res += print_string_width(output, flags, d, precise, s);

	precise = (precise == -1) ? s : precise;
	for (index = 0; *(str + index) != '\0' && index < precise; index++)
	{
		if (*(str + index) < 32 || *(str + index) >= 127)
		{
			res += _memcpy(output, hex, 2);
			if (*(str + index) < 16)
				res += _memcpy(output, &zero, 1);
			res += unsigned_base(output, *(str + index),
						 "0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		res += _memcpy(output, (str + index), 1);
	}

	res += print_neg_width(output, res, flags, d);

	return (res);
}

/**
 * print_r - reverses a string
 * @ap: variable arguments
 * @flags: flag modifiers.
 * @d: width modifier.
 * @precise: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct that stores a character array.
 *
 * Return: number of bytes stored
 */
unsigned int print_r(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	char *str, *null = "(null)";
	int s, end, i;
	unsigned int res = 0;

	(void)flags;
	(void)len;

	str = va_arg(ap, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (s = 0; *(str + s);)
		s++;

	res += print_string_width(output, flags, d, precise, s);

	end = s - 1;
	precise = (precise == -1) ? s : precise;
	for (i = 0; end >= 0 && i < precise; i++)
	{
		res += _memcpy(output, (str + end), 1);
		end--;
	}

	res += print_neg_width(output, res, flags, d);

	return (res);
}

/**
 * print_R - Converts a string to ROT13
 * @ap: variable arguments
 * @flags: flag modifiers
 * @d: width modifier.
 * @precise: precision modifier.
 * @len: lenth modifier.
 * @output: buffer_t struct that stores a character array.
 *
 * Return: number of bytes stored
 */
unsigned int print_R(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, s;
	unsigned int res = 0;

	(void)flags;
	(void)len;

	str = va_arg(ap, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (s = 0; *(str + s);)
		s++;

	res += print_string_width(output, flags, d, precise, s);

	precise = (precise == -1) ? s : precise;
	for (i = 0; *(str + i) != '\0' && i < precise; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + i) == *(alpha + j))
			{
				res += _memcpy(output, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			res += _memcpy(output, (str + i), 1);
	}

	res += print_neg_width(output, res, flags, d);

	return (res);
}
