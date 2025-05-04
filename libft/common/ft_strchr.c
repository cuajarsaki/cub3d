/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:36:08 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if ((unsigned char) s[i] == (unsigned char) c)
			return ((char *)(s + i));
		i ++;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	char *s = "tHello World";
// 	char *p1 = ft_strchr(s, 't' + 256);
// 	char *p2 = strchr(s, 't' + 256);
// 	printf("%p\n", p1);
// 	printf("%p\n", p2);
// 	// strchr(NULL, 't' + 256); // Error
// }
