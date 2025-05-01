/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:53:40 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	size_t	len;
	size_t	i;
	char	*str_cp;

	len = ft_strlen(string);
	str_cp = (char *) malloc(sizeof(char) * (len + 1));
	if (str_cp == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str_cp[i] = string[i];
		i ++;
	}
	str_cp[i] = '\0';
	return (str_cp);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char *s;
// 	s = ft_strdup("ABCDEFG");
// 	printf("%s\n", s);
// 	free(s);
// 	s = ft_strdup("");
// 	printf("%s\n", s);
// 	free(s);
// 	// s = ft_strdup(NULL); //Error
// 	// printf("%s\n", s);
// 	// free(s);

// 	s = strdup("ABCDEFG");
// 	printf("%s\n", s);
// 	free(s);
// 	s = strdup("");
// 	printf("%s\n", s);
// 	free(s);
// 	// s = strdup(NULL); //Error
// 	// printf("%s\n", s);
// 	// free(s);
// }