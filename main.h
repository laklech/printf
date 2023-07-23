#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Prototypes */
int get_char(va_list character); /* Function to return char */
int get_bin(va_list binary); /* Function to write binary */
int _putchar(char c); /* Function to print char */
int _strlen(char *string); /* Function to get string length */
int _oct(va_list octal); /* Function to print octal digits */
int string(va_list *s); /* Function to print string to stdout */
int write_rot13(va_list rot); /* Function to get rot13 version of digits */
int get_int(va_list integer); /* Function to print integers */
int _hex_str(unsigned int n, unsigned int hex, char alpha); /* Change to hex */
int _unsigned(va_list unsign); /* Print unsigned int to stdout */
int _printf(const char *format, ...); /* Prints output according to format */
int print_op(const char *format, fmt_t *print_arr, va_list list); /* Check which specifier to print */
int _hex_len(va_list hex); /* Find length of hexadecimal number */
int _hex_unsigned(va_list hex); /* Prints unsigned hex to output */

/* Structure Function */

/**
 * struct fmt - function to check for formats
 * @type: the format to print
 * @f: the print function to use
 */
typedef struct fmt
{
	char *type;
	int (*f)();
} fmt_t;

#endif
