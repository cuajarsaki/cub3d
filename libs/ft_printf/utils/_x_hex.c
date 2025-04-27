/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _x_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:36:48 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	add_options(int options, int upper);

int	x_print_dec_upper(va_list args, int options)
{
	int				digits;
	unsigned int	value;
	uintptr_t		ulong_value;

	digits = 0;
	value = va_arg(args, unsigned int);
	ulong_value = (uintptr_t) value;
	if (ulong_value != 0)
		digits = add_options(options, 1);
	digits += dec_to_nbase(ulong_value, "0123456789ABCDEF", STDOUT_FILENO);
	return (digits);
}

int	x_print_dec_lower(va_list args, int options)
{
	int				digits;
	unsigned int	value;
	uintptr_t		ulong_value;

	digits = 0;
	value = va_arg(args, unsigned int);
	ulong_value = (uintptr_t) value;
	if (ulong_value != 0)
		digits = add_options(options, 0);
	digits += dec_to_nbase(ulong_value, "0123456789abcdef", STDOUT_FILENO);
	return (digits);
}

static int	add_options(int options, int upper)
{
	int		digits;
	char	*prefix;

	digits = 0;
	prefix = "0x\0";
	if (upper)
		prefix = "0X\0";
	if (options & 1)
	{
		while (*prefix != '\0')
		{
			if (write(STDOUT_FILENO, prefix, 1) != -1)
				digits ++;
			prefix ++;
		}
	}
	return (digits);
}

// int	test_helper_upper(const char *fmt, ...)
// {
// 	va_list	args;
// 	int		a;

// 	va_start(args, fmt);
// 	a = x_print_dec_upper(args, 0b100);
// 	va_end(args);
// 	return (a);
// }

// int	test_helper_lower(const char *fmt, ...)
// {
// 	va_list	args;
// 	int		a;

// 	va_start(args, fmt);
// 	a = x_print_dec_lower(args, 0b100);
// 	va_end(args);
// 	return (a);
// }

// #include <stdio.h>
// int	main(void)
// {
// 	int	a;

// 	a = test_helper_upper("", 4294967295);
// 	printf("\n%d\n", a);
// 	a = test_helper_upper("", 2147483647);
// 	printf("\n%d\n", a);
// 	a = test_helper_upper("", -2147483648);
// 	printf("\n%d\n", a);
// 	a = test_helper_upper("", -2147483649);
// 	printf("\n%d\n", a);
// 	printf("--------------\n");
// 	a = test_helper_lower("", 4294967295);
// 	printf("\n%d\n", a);
// 	a = test_helper_lower("", 2147483647);
// 	printf("\n%d\n", a);
// 	a = test_helper_lower("", -2147483648);
// 	printf("\n%d\n", a);
// 	a = test_helper_lower("", -2147483649);
// 	printf("\n%d\n", a);
// 	printf("--------------\n");
// 	a = printf("%x", 4294967295);
// 	printf("\n%d\n", a);
// 	a = printf("%x", 2147483647);
// 	printf("\n%d\n", a);

// 	a = ft_printf("%#x", -214748364);
// 	printf("\n%d\n", a);
// 	a = printf("%#x", -214748364);
// 	printf("\n%d\n", a);
// }
