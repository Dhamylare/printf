#include "main.h"

void clean(va_list ap, buffer_t *output);
int r_printf(const char *format, va_list ap, buffer_t *output);
int _printf(const char *format, ...);

/**
 * clean - Peforms cleanup operations for _printf.
 * @ap: arguments
 * @output: A buffer_t struct.
 */
void clean(va_list ap, buffer_t *output)
{
	va_end(ap);
	write(1, output->start, output->len);
	free_buffer(output);
}

/**
 * r_printf - reads through the format string for _printf.
 * @format: character string to print
 * @output: struct containing a buffer
 * @ap: arguments
 * Return: The number of characters stored to output.
 */
int r_printf(const char *format, va_list ap, buffer_t *output)
{
	int i, d, precise, res = 0;
	char temp;
	unsigned char flags, len;
	unsigned int (*f)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		len = 0;
		if (*(format + i) == '%')
		{
			temp = 0;
			flags = h_flags(format + i + 1, &temp);
			d = h_width(ap, format + i + temp + 1, &temp);
			precise = h_precision(ap, format + i + temp + 1,
					&temp);
			len = h_length(format + i + temp + 1, &temp);

			f = h_specifiers(format + i + temp + 1);
			if (f != NULL)
			{
				i += temp + 1;
				res += f(ap, output, flags, d, precise, len);
				continue;
			}
			else if (*(format + i + temp + 1) == '\0')
			{
				res = -1;
				break;
			}
		}
		res += _memcpy(output, (format + i), 1);
		i += (len != 0) ? 1 : 0;
	}
	clean(ap, output);
	return (res);
}

/**
 * _printf - prints a formatted output.
 * @format: formatted string to be printed
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list ap;
	int res;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(ap, format);

	res = r_printf(format, ap, output);

	return (res);
}
