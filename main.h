#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <limits.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* Sizes */
#define S_SHORT 1
#define S_LONG 2

/* Flags */
#define F_PLUS 2
#define F_HASH 8
#define F_MINUS 1
#define F_SPACE 16
#define F_ZERO 4

/* Prototypes */
int get_char(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Return char */
int get_bin(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Write binary */
int get_oct(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Print octal digits*/
int get_string(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Print string */
int write_rot13(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Get rot13 version */

int get_int(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Print integers */
int get_hex_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Change to hex */
int get_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Print unsigned int*/
int _printf(const char *format, ...); /* Prints output according to format */
int get_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Length of hex */
int write_unsigned(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size); /* Prints unsigned */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Handle percentage */
int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size); /*non-printable chars*/
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Memory address */

int get_flags(const char *format, int *i); /* Handle flags */
int get_width(const char *format, int *i, va_list list); /* Handle width */
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i); /* Handle size */
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size); /* Reverse string */

int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size); /* Handle char width */
int write_number(int is_positive, int ind, char buffer[],
	int flags, int width, int precision, int size); /* Handle int width */
int write_num(int ind, char bff[], int flags, int width, int precision,
	int length, char padd, char extra_c); /* handle integer width */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start);

int is_printable(char); /* Check if string is printable */
int append_hexa_code(char, char[], int); /* Appends code for hexadecimal */
int is_digit(char); /* Check if string contains digits */

long int convert_size_number(long int num, int size); /* Handle long int */
long int convert_size_unsgnd(unsigned long int num, int size);

/* Structure Function */

/**
 * struct fmt - function to check for formats
 * @fmt: the format to print
 * @f: the print function to use
 */
struct fmt
{
	char fmt;
	int (*f)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fmt_t: The function associated.
 */
typedef struct fmt fmt_t;

int handle_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

#endif
