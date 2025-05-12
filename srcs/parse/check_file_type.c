/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:40:33 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/10 17:50:47 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_dir(char *file)
{
    int		fd;
    bool	is_dir;

	is_dir = false;
	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		is_dir = true;
	}
	return (is_dir);
}

static bool	is_cub_file(char *file)
{
	size_t	len;
	char	*extension;
	
	len = ft_strlen(file);
	extension = file + (len - 4); 
	if (ft_strncmp(extension, ".cub", 4) != 0)
		return (false);
	return (true);
}

static bool	is_xpm_file(char *file)
{
	size_t	len;
	char	*extension;

	len = ft_strlen(file);
	extension = file + (len - 4);
	if (ft_strncmp(extension, ".xpm", 4) != 0)
		return (false);
	return (true);
}

int	check_file_type(char *file, int file_type)
{
    int fd;

    if (is_dir(file))
		return (err_msg(file, ERR_FILE_IS_DIR, FAILURE));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err_msg(file, strerror(errno), FAILURE));
	close(fd);
	if (file_type == CUB && !is_cub_file(file))
		return (err_msg(file, ERR_FILE_NOT_CUB, FAILURE));
	if (file_type == XPM && !is_xpm_file(file))
		return (err_msg(file, ERR_FILE_NOT_XPM, FAILURE));
	return (SUCCESS);
}
