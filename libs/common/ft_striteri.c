/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 08:52:04 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (f == NULL || s == NULL)
		return ;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i ++;
	}
	return ;
}

// void	my_lower(unsigned int index, char *c)
// {
// 	if ('A' <= *c && *c <= 'Z')
// 		*c += 'a' - 'A';
// 	return ;
// }

// int main()
// {
// 	char s[] = "ABCDEFG";
// 	// char *s;
// 	// s = NULL;
// 	ft_striteri(s, my_lower);
// 	ft_striteri(s, NULL);
// }
