/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:39:11 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = '\0';
	return (src_len);
}

// #include <string.h>
// #include <stdio.h>
// 	int main(){
// 	char	src1[] = {"abcde"};
// 	char	src2[] = {"abcde"};
// 	char	dst1[] = {"Red Sky in Morning Sailor take wArning"};
// 	char	dst2[] = {"Red Sky in Morning Sailor take wArning"};
// 	size_t	n1;
// 	unsigned int	n2;

// 	// n1 = strlcpy(dst1, src1, 0);
// 	n2 = ft_strlcpy(dst2, src1, 0);
// 	printf("src:%s\tdist:%s\n", src1, dst1);
// 	printf("src:%s\tdist:%s\n", src2, dst2);

// 	// n1 = strlcpy(dst1, src1, 5);
// 	n2 = ft_strlcpy(dst2, src1, 5);
// 	printf("src:%s\tdist:%s\n", src1, dst1);
// 	printf("src:%s\tdist:%s\n", src2, dst2);

// 	// n1 = strlcpy(dst1, src1, 6);
// 	n2 = ft_strlcpy(dst2, src1, 6);
// 	printf("src:%s\tdist:%s\n", src1, dst1);
// 	printf("src:%s\tdist:%s\n", src2, dst2);

// 	// n1 = strlcpy(dst1, src1, 99);
// 	n2 = ft_strlcpy(dst2, src1, 99);
// 	// printf("src:%s\tdist:%s\n", src1, dst1);
// 	printf("src:%s\tdist:%s\n", src2, dst2);
// }
