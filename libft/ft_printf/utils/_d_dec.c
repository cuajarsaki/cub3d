/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _d_dec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:36:38 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	d_print_dec(va_list args, int options)
{
	int				value;
	int				digits;
	unsigned int	uint_value;
	uintptr_t		ulong_value;

	value = va_arg(args, int);
	digits = 0;
	if (value >= 0)
	{
		uint_value = value;
		if (options & 4 && write(STDOUT_FILENO, "+", 1) != -1)
			digits += 1;
		else if (options & 2 && write(STDOUT_FILENO, " ", 1) != -1)
			digits += 1;
	}
	else
	{
		uint_value = (unsigned int)(-1 * value);
		if (write(STDOUT_FILENO, "-", 1) != -1)
			digits += 1;
	}
	ulong_value = (uintptr_t) uint_value;
	digits += dec_to_nbase(ulong_value, "0123456789", STDOUT_FILENO);
	return (digits);
}

// int	test_helper(const char *fmt, ...)
// {
// 	va_list		args;
// 	uintptr_t	value;
// 	int			len;

// 	va_start(args, fmt);
// 	len = d_print_dec(args, 0b110);
// 	va_end(args);
// 	return (len);
// }

// #include <stdio.h>
// int	main(void)
// {
// 	int		len;

// 	len = test_helper("", 2147483647);
// 	printf("\n%d\n", len);
// 	len = printf("%d", 2147483647);
// 	printf("\n%d\n", len);

// 	len = test_helper("", -2147483648);
// 	printf("\n%d\n", len);
// 	len = printf("%d", -2147483648);
// 	printf("\n%d\n", len);

// 	len = test_helper("", -100);
// 	printf("\n%d\n", len);
// 	len = printf("%d", -100);
// 	printf("\n%d\n", len);
// }
