#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/* flag modifiers' macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* length modifiers' macros */
#define SHORT 1
#define LONG 2

/**
 * struct buffer_s - new type defining a buffer struct.
 * @buffer: pointer to a character array.
 * @start: pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */
typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;

/**
 * struct print_s - new type defining a converter struct.
 * @specifier: character representing a conversion specifier.
 * @func: pointer to a conversion function corresponding to specifier.
 */
typedef struct print_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} print_t;

/**
 * struct flag_s - new type defining flags struct.
 * @flag: character representing a flag.
 * @value: integer value of the flag.
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);

unsigned int print_c(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_s(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_di(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_percent(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_b(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_u(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_o(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_x(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_X(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_S(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_p(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_r(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned int print_R(va_list ap, buffer_t *output,
		unsigned char flags, int d, int precise, unsigned char len);
unsigned char h_flags(const char *flags, char *index);
unsigned char h_length(const char *modifier, char *index);
int h_width(va_list ap, const char *modifier, char *index);
int h_precision(va_list ap, const char *modifier, char *index);
unsigned int (*h_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int d);
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int d, int precise, int s);
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int d);

buffer_t *init_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
unsigned int long_base(buffer_t *output, long int num, char *ptr,
		unsigned char flags, int d, int precise);
unsigned int unsigned_base(buffer_t *output, unsigned long int num, char *ptr,
		unsigned char flags, int d, int precise);

#endif
