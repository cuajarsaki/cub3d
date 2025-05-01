/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:05:57 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

typedef int	(*t_func_pt)(void *, ...);

int			ft_printf(const char *fmt, ...);

// sub functions
/* write uintptr_t number as n base number */
int			dec_to_nbase(uintptr_t n, char *base, int fd);
/* switch functions */
t_func_pt	switch_fmt_render(char specifier);

// usecase functions
/* %c Prints a single character. */
int			c_print_char(va_list args);
/* %s Prints a string (as defined by the common C convention). */
int			s_print_str(va_list args);
/* %p The void * pointer argument has to be printed in hexadecimal format. */
int			p_print_pt(va_list args);
/* %d Prints a decimal (base 10) number. */
int			d_print_dec(va_list args, int option);
/* %i Prints an integer in base 10. */
int			i_print_dec(va_list args, int option);
/* %u Prints an unsigned decimal (base 10) number. */
int			u_print_dec(va_list args);
/* %x Prints a number in hexadecimal (base 16) lowercase format. */
int			x_print_dec_lower(va_list args, int option);
/* %X Prints a number in hexadecimal (base 16) uppercase format. */
int			x_print_dec_upper(va_list args, int option);
/* %% Prints a percent sign. */
int			_print_percent(va_list args);
/* detect wrong format i.e. %w */
int			_other_format(va_list args, int options, char c);

#endif
