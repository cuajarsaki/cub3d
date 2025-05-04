/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:29:03 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int		duplicate_sentence(int fd, char **dst, char *buff);
static ssize_t	read_buffer_size(int fd, char *buff);
static void		shift_buffer(char *buff);

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*result_str;
	size_t		offset;

	if (fd < 0 || FOPEN_MAX <= fd)
		return (NULL);
	offset = index_strchr(buffer[fd], '\n', BUFFER_SIZE);
	result_str = gnl_ft_substr(buffer[fd], 0, offset + 1);
	if (result_str == NULL)
		return (NULL);
	if (index_strchr(result_str, '\n', BUFFER_SIZE) != BUFFER_SIZE)
	{
		shift_buffer(buffer[fd]);
		return (result_str);
	}
	if (duplicate_sentence(fd, &result_str, buffer[fd]))
	{
		free (result_str);
		return (NULL);
	}
	shift_buffer(buffer[fd]);
	return (result_str);
}

static int	duplicate_sentence(int fd, char **dst, char *buff)
{
	char		*new_str;
	char		*result_str;
	size_t		offset;

	new_str = NULL;
	while (read_buffer_size(fd, buff) > 0)
	{
		new_str = gnl_ft_strjoin(*dst, buff);
		if (new_str == NULL)
			return (1);
		free(*dst);
		*dst = new_str;
		if (index_strchr(buff, '\n', BUFFER_SIZE) != BUFFER_SIZE)
			break ;
	}
	if (**dst == '\0')
		return (1);
	offset = index_strchr(*dst, '\n', gnl_ft_strlen(*dst));
	result_str = gnl_ft_substr(*dst, 0, offset + 1);
	free(*dst);
	if (result_str == NULL)
		return (1);
	*dst = result_str;
	return (0);
}

static ssize_t	read_buffer_size(int fd, char *buff)
{
	ssize_t	i;
	ssize_t	read_bytes;

	i = 0;
	while (i < BUFFER_SIZE)
		buff[i ++] = '\0';
	read_bytes = read(fd, buff, BUFFER_SIZE);
	return (read_bytes);
}

static void	shift_buffer(char *buff)
{
	ssize_t	i;
	ssize_t	index;
	char	*src;

	i = 0;
	index = index_strchr(buff, '\n', BUFFER_SIZE);
	src = buff + index + 1;
	while (index < BUFFER_SIZE)
	{
		buff[i] = src[i];
		index ++;
		i ++;
	}
	while (i < BUFFER_SIZE)
		buff[i++] = '\0';
	return ;
}
