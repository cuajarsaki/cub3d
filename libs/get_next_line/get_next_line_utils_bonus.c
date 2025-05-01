/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:00:11 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s ++)
		len ++;
	return (len);
}

char	*gnl_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	s_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s_len = gnl_ft_strlen(s);
	if (s_len < start)
		start = s_len;
	if (s_len - start < len)
		len = s_len - start;
	result = (char *) malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[i + start] != '\0')
	{
		result[i] = (s + start)[i];
		i ++;
	}
	result[len] = '\0';
	return (result);
}

char	*gnl_ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = gnl_ft_strlen(s1);
	s2_len = gnl_ft_strlen(s2);
	result = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len && s1[i] != '\0')
	{
		result[i] = s1[i];
		i ++;
	}
	while (i < s1_len + s2_len && s2[i - s1_len] != '\0')
	{
		result[i] = s2[i - s1_len];
		i ++;
	}
	result[s1_len + s2_len] = '\0';
	return (result);
}

size_t	index_strchr(const char *s, char c, size_t size)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = gnl_ft_strlen(s);
	while (i < s_len)
	{
		if (s[i] == c)
			return (i);
		i ++;
	}
	return (size);
}
