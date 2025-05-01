/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchung <pchung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:36:11 by pchung            #+#    #+#             */
/*   Updated: 2025/04/27 17:01:07 by pchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifdef BUFFER_SIZE
# else
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);

size_t	gnl_ft_strlen(const char *s);
char	*gnl_ft_substr(char const *s, unsigned int start, size_t len);
char	*gnl_ft_strjoin(char const *s1, char const *s2);

size_t	index_strchr(const char *s, char c, size_t size);

#endif
