/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _s_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:36:43 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	s_print_str(va_list args)
{
	char	*value;
	int		digits;

	value = va_arg(args, char *);
	digits = 0;
	if (value == NULL)
		value = "(null)";
	while (*value != '\0')
	{
		if (write(STDOUT_FILENO, value, 1) != -1)
			digits ++;
		value ++;
	}
	return (digits);
}

// void	test_helper(const char *fmt, ...)
// {
// 	va_list		args;

// 	va_start(args, fmt);
// 	s_print_str(args);
// 	va_end(args);
// }

// int	main(void)
// {
// 	test_helper("", "Hello");
// }
