/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:29 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	src;

	i = 0;
	dst = (unsigned char *) s;
	src = (unsigned char) c;
	while (i < n)
	{
		dst[i] = src;
		i ++;
	}
	return (s);
}

// #include <stdio.h>
// int main(){
// 	char str[] = "Hello World";
// 	ft_memset(str, 32, 10);
// 	printf("%s\n", str);
// }
