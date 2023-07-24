#include "main.h"

void print_buff(char buffer[], int *buff_ind);

/**
 * _printf - writes output according to format
 * @format: string to be considered
 * Return: the character to be printed
 */

int _printf(const char *format, ...)
{
	va_list list;
	int f, write = 0, pc = 0;
	char buffer[BUFF_SIZE];
	int size, flags, width, precision, buff_ind = 0;

	if (format == NULL)
		return (-1);
	va_start(list, format);

	for (f = 0; format && format[f] != '\0'; f++)
	{
		if (format[f] != 37)
		{
			buffer[buff_ind++] = format[f];
			if (buff_ind == BUFF_SIZE)
				print_buff(buffer, &buff_ind);
			/* write(1, &format[f], 1); */
			pc++;
		}
		else
		{
			print_buff(buffer, &buff_ind);
			flags = get_flags(format, &f);
			width = get_width(format, &f, list);
			precision = get_precision(format, &f, list);
			size = get_size(format, &f);
			f++;
			write = handle_print(format, &f, list, buffer,
				flags, width, precision, size);
			if (write == -1)
				return (-1);
			pc += write;
		}
	}
	print_buff(buffer, &buff_ind);
	va_end(list);
	return (pc);
}

/**
 * print_buff - function to print buffer if it exists
 * @buffer: array of chars
 * @buff_ind: index of buffer to print next char
 */

void print_buff(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}
