#include "main.h"

/**
 * handle_print - function that prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: index to print
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: handle width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 when successful otherwise 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int k, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', get_char}, {'s', get_string}, {'%', print_percent},
		{'i', get_int}, {'d', get_int}, {'b', get_bin},
		{'u', get_unsigned}, {'o', get_oct}, {'x', get_hexadecimal},
		{'X', get_hex_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', write_rot13}, {'\0', NULL}
	};
	for (k = 0; fmt_types[k].fmt != '\0'; k++)
		if (fmt[*ind] == fmt_types[k].fmt)
			return (fmt_types[k].f(list, buffer, flags, width, precision, size));

	if (fmt_types[k].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
