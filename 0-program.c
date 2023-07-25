#include "main.h"
#define UNUSED(x) (void)(x)

/**
 * get_char - Function that prints a char
 * @types: List of arguments
 * @buffer: Array buffer to handle print
 * @flags:  Calculates active flags
 * @width: Width handler
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int get_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char m = va_arg(types, int);

	return (handle_write_char(m, buffer, flags, width, precision, size));
}

/**
 * print_percent - function that prints a percent sign
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Handle width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars written
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * get_int - function that returns integer
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Checks active flags
 * @width: handle width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Chars printed
 */
int get_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int d = BUFSIZ - 2;
	int is_negative = 0;
	long int b = va_arg(types, long int);
	unsigned long int num;

	b = convert_size_number(b, size);

	if (b == 0)
		buffer[d--] = '0';

	buffer[BUFSIZ - 1] = '\0';
	num = (unsigned long int)b;

	if (b < 0)
	{
		num = (unsigned long int)((-1) * b);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[d--] = (num % 10) + '0';
		num /= 10;
	}
	d++;
	return (write_number(is_negative, d, buffer, flags, width, precision, size));
}

/**
 * get_bin - function that prints an unsigned number
 * @types: the list of arguments
 * @buffer: Array of buffer to handle print
 * @flags:  Checks active flags
 * @width: handle width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: the number of char printed.
 */
int get_bin(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, v, q, add;
	unsigned int c[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	v = 2147483648; /* The arithmetic of (2 ^ 31) */
	c[0] = x / v;
	for (q = 1; q < 32; q++)
	{
		v /= 2;
		c[q] = (x / v) % 2;
	}
	for (q = 0, add = 0, count = 0; q < 32; q++)
	{
		add += c[q];
		if (add || q == 31)
		{
			char z = '0' + c[q];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

/**
 * get_string - function that prints a string
 * @types: List of arguments
 * @buffer: Array of buffer to handle print
 * @flags:  Checks active flags
 * @width: handle width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: the number of chars printed
 */
int get_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int m, length = 0;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (m = width - length; m > 0; m--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (m = width - length; m > 0; m--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}
