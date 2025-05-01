/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 06:18:28 by vscode            #+#    #+#             */
/*   Updated: 2023/11/25 06:21:27 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_func_pt	switch_fmt_render(char specifier)
{
	if (specifier == 'c')
		return ((t_func_pt) c_print_char);
	else if (specifier == 's')
		return ((t_func_pt) s_print_str);
	else if (specifier == 'p')
		return ((t_func_pt) p_print_pt);
	else if (specifier == 'd')
		return ((t_func_pt) d_print_dec);
	else if (specifier == 'i')
		return ((t_func_pt) i_print_dec);
	else if (specifier == 'u')
		return ((t_func_pt) u_print_dec);
	else if (specifier == 'x')
		return ((t_func_pt) x_print_dec_lower);
	else if (specifier == 'X')
		return ((t_func_pt) x_print_dec_upper);
	else if (specifier == '%')
		return ((t_func_pt) _print_percent);
	else
		return ((t_func_pt) _other_format);
}
