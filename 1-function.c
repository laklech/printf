#include "main.h"

/**
 * get_unsigned - function that prints an unsigned number
 * @types: List of arguments
 * @buffer: array of buffer to handle print
 * @flags:  Checks active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int get_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int h = BUFF_SIZE - 2;
	unsigned long int dig = va_arg(types, unsigned long int);

	dig = convert_size_unsgnd(dig, size);

	if (dig == 0)
		buffer[h--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (dig > 0)
	{
		buffer[h--] = (dig % 10) + '0';
		dig /= 10;
	}
	h++;
	return (write_unsgned(0, h, buffer, flags, width, precision, size));
}

/**
 * get_hexadecimal - Prints an unsigned number in hexadecimal version
 * @types: List of arguments
 * @buffer: Array of buffer to handle print
 * @flags:  Checks active flags
 * @width: handle width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int get_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * get_oct - Prints an unsigned number in octal version
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Checks active flags
 * @width: handle width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int get_oct(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int v = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[v--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[v--] = (num % 8) + '0';
		num /= 8;
	}
	if (flags & F_HASH && init_num != 0)
		buffer[v--] = '0';
	v++;
	return (write_unsgned(0, v, buffer, flags, width, precision, size));
}

/**
 * print_hexa - Returns a hexadecimal number in lower or upper
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Checks active flags
 * @flag_ch: Checks active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int c = BUFF_SIZE - 2;
	unsigned long int dig = va_arg(types, unsigned long int);
	unsigned long int init_num = dig;

	UNUSED(width);

	dig = convert_size_unsgnd(num, size);

	if (dig == 0)
		buffer[c--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (dig > 0)
	{
		buffer[c--] = map_to[dig % 16];
		dig /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[c--] = flag_ch;
		buffer[c--] = '0';
	}
	c++;
	return (write_unsgned(0, c, buffer, flags, width, precision, size));
}

/**
 * get_hex_upper - Prints an unsigned number in upper hexadecimal version
 * @types: List of arguments
 * @buffer: Array buffer to handle print
 * @flags:  Checks active flags
 * @width: handle width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int get_hex_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}
