#include "main.h"

unsigned char h_flags(const char *flag, char *index);
unsigned char h_length(const char *modifier, char *index);
int h_width(va_list ap, const char *modifier, char *index);
int h_precision(va_list ap, const char *modifier, char *index);
unsigned int (*h_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/**
 * h_flags - match flags with corresponding value
 * @flag: pointer to string of flags
 * @index: index counter
 *
 * Return: return the value of flag characters
 */
unsigned char h_flags(const char *flag, char *index)
{
	int i, j;
	unsigned char res = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (res == 0)
					res = flags[j].value;
				else
					res |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (res);
}

/**
 * h_length - length of modifiers with their corresponding value.
 * @modifier: pointer to a length modifier
 * @index: index counter
 * Return: length modifier value
 */
unsigned char h_length(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * h_width - Match a width modifier with its corresponding value
 * @ap: variable argument
 * @modifier: pointer to a width modifier.
 * @index: index counter
 * Return: value of width modifier
 */
int h_width(va_list ap, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(ap, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * h_precision - Matches a precision modifier with its value
 * @ap: variable arguments
 * @modifier: pointer precision modifier
 * @index: index counter
 * Return: value of precision modifier
 */
int h_precision(va_list ap, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
		 *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
		   (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(ap, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * h_specifiers - Matches conversion specifier with a corresponding function
 * @specifier: pointer to a conversion specifier
 * Return: a pointer to the function or NULL.
 */
unsigned int (*h_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int i;
	print_t print[] = {
		{'c', print_c},
		{'s', print_s},
		{'d', print_di},
		{'i', print_di},
		{'%', print_percent},
		{'b', print_b},
		{'u', print_u},
		{'o', print_o},
		{'x', print_x},
		{'X', print_X},
		{'S', print_S},
		{'p', print_p},
		{'r', print_r},
		{'R', print_R},
		{0, NULL}
	};

	for (i = 0; print[i].func; i++)
	{
		if (print[i].specifier == *specifier)
			return (print[i].func);
	}

	return (NULL);
}
