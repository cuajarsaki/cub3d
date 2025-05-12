/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:29:52 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/09 18:35:03 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_row(char *file)
{
	int		fd;
	char	*line;
	int		row_count;

	row_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg(file, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			row_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (row_count);
}

void	dup_content(char **content, char *file)
{
	int		fd;
	char 	*line;
	int		row;
	int		column;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg(file, strerror(errno), errno);
	else
	{
		row = 0;
		line = get_next_line(fd);
		while (line != NULL)
		{
			column = 0;
			content[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
			if (!content[row])
			{
				err_msg(NULL, ERR_MALLOC, 0);
				return (free_tab((void **)content));
			}
			while (line[column] != '\0')
			{
				content[row][column] = line[column];
				column++;
			}
			content[row++][column] = '\0';
			free(line);
			line = get_next_line(fd);
		}
	}
	close(fd);
}

void	parse_game(t_game *game, char *file)
{
	int	row;
	// int	column;

	row = count_row(file);
	game->content = ft_calloc(row + 1, sizeof(char *));
	if (!game->content)
	{
		err_msg(NULL, ERR_MALLOC, 0); // todo: malloc failは0なの？
		return ;
	}
	dup_content(game->content, file);
}
