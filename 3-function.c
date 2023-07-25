#include "main.h"
#define UNUSED(x) (void)x

/**
 * print_pointer - function that prints the memory address of a variable
 * @types: List of arguments
 * @buffer: Array of buffer to handle print
 * @flags:  Checks active flags
 * @width: handle width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int index = BUFSIZ - 2, length = 2, padd_start = 1;
	/* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFSIZ - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[index--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	index++;

	/*return (write(1, &buffer[i], BUFSIZ - i - 1));*/
	return (write_pointer(buffer, index, length,
		width, flags, padd, extra_c, padd_start));
}

/**
 * print_reverse - function that prints reverse string
 * @types: List of arguments
 * @buffer: Array of buffer to handle print
 * @flags:  Checks active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int b, check = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (b = 0; str[b]; b++)
		;

	for (b = b - 1; b >= 0; b--)
	{
		char z = str[b];

		write(1, &z, 1);
		check++;
	}
	return (check);
}

/**
 * write_rot13 - function that print a string in rot13.
 * @types: List of arguments
 * @buffer: Array of buffer to handle print
 * @flags:  Checks active flags
 * @width: handle width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int write_rot13(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int m, q;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (m = 0; str[m]; m++)
	{
		for (q = 0; in[q]; q++)
		{
			if (in[q] == str[m])
			{
				x = out[q];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[q])
		{
			x = str[m];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: List of arguments
 * @buffer: Array of buffer to handle print
 * @flags:  Checks active flags
 * @width: handle width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int n = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[n] != '\0')
	{
		if (is_printable(str[n]))
			buffer[n + offset] = str[n];
		else
			offset += append_hexa_code(str[n], buffer, n + offset);

		n++;
	}

	buffer[n + offset] = '\0';

	return (write(1, buffer, n + offset));
}
