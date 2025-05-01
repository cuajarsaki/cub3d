/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:05:57 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					dec_to_nbase(uintptr_t n, char *base, int fd);
static int			get_options(const char *part_str, int *index);
static char			*ft_printf_strchr(const char *s, int c);
static size_t		ft_printf_strlen(const char *s);

int	ft_printf(const char *fmt, ...)
{
	va_list		args;
	int			i;
	int			cnt;
	int			options;

	va_start(args, fmt);
	i = 0;
	cnt = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			options = get_options(&fmt[i + 1], &i);
			cnt += switch_fmt_render(fmt[i + 1])(args, options, fmt[i + 1]);
			i ++;
		}
		else if (write(STDOUT_FILENO, &fmt[i], 1) != -1)
			cnt ++;
		i ++;
	}
	va_end(args);
	return (cnt);
}

static int	get_options(const char *part_str, int *index)
{
	char	*extra_fmt;
	char	*location;
	int		options;
	int		diff;

	options = 0;
	extra_fmt = "# +";
	while (1)
	{
		location = ft_printf_strchr(extra_fmt, (int)*part_str);
		if (location == NULL)
			break ;
		diff = (int)(location - extra_fmt);
		options |= (1 << diff);
		part_str ++;
		(*index)++;
	}
	return (options);
}

int	dec_to_nbase(uintptr_t n, char *base, int fd)
{
	uintptr_t	base_num;
	uintptr_t	residual;
	int			cnt;

	base_num = (uintptr_t) ft_printf_strlen(base);
	if (n < base_num)
	{
		if (write(fd, &base[n], 1) == -1)
			return (0);
		return (1);
	}
	residual = n % base_num;
	cnt = dec_to_nbase(n / base_num, base, fd);
	if (write(fd, &base[residual], 1) == -1)
		return (cnt);
	return (cnt + 1);
}

static char	*ft_printf_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_printf_strlen(s);
	while (i <= len)
	{
		if ((unsigned char) s[i] == (unsigned char) c)
			return ((char *)(s + i));
		i ++;
	}
	return (NULL);
}

static size_t	ft_printf_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s ++)
		len ++;
	return (len);
}
