/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _p_pt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:36:40 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_print_pt(va_list args)
{
	uintptr_t	value;
	char		*prefix;
	int			digits;

	value = va_arg(args, uintptr_t);
	prefix = "0x\0";
	digits = 0;
	while (*prefix != '\0')
	{
		if (write(STDOUT_FILENO, prefix, 1) != -1)
			digits ++;
		prefix ++;
	}
	digits += dec_to_nbase(value, "0123456789abcdef", STDOUT_FILENO);
	return (digits);
}

// int	p_print_pt_linux(va_list args)
// {
// 	uintptr_t	value;
// 	char		*prefix;
// 	int			digits;

// 	value = va_arg(args, uintptr_t);
// 	prefix = "0x\0";
// 	if (value == 0)
// 		prefix = "(nil)";
// 	digits = 0;
// 	while (*prefix != '\0')
// 	{
// 		if (write(STDOUT_FILENO, prefix, 1) != -1)
// 			digits ++;
// 		prefix ++;
// 	}
// 	if (value == 0)
// 		return (digits);
// 	digits += dec_to_nbase(value, "0123456789abcdef", STDOUT_FILENO);
// 	return (digits);
// }

// int	test_helper(const char *fmt, ...)
// {
// 	va_list		args;
// 	uintptr_t	value;
// 	int			len;

// 	va_start(args, fmt);
// 	len = p_print_pt(args);
// 	va_end(args);
// 	return (len);
// }

// #include <stdio.h>
// int	main(void)
// {
// 	char	str[] = "Hello";
// 	int		len;

// 	len = test_helper("", str);
// 	printf("\n%d\n", len);
// 	len = printf("%p", str);
// 	printf("\n%d\n", len);
// }
