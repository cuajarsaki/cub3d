/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:04:29 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/10 01:48:20 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	no_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (true);
		i++;
	}
	return (false);
}

static int	*rgb_atoi(char **rgb_str, int *rgb_num)
{
	int	i;

	i = 0;
	while (rgb_str[i])
	{
		if (no_digit(rgb_str[i]))
		{
			free_tab((void **)rgb_str);
			free(rgb_num);
			return (NULL);
		}
		// todo: atoiに失敗したらどうなる？
		rgb_num[i] = ft_atoi(rgb_str[i]);
		i++;
	}
	free_tab((void **)rgb_str);
	return (rgb_num);
}

static int	*get_rgb(char *line, int j)
{
	char	**rgb_str;
	int		count;
	int		*rgb_num;
	int		len;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && line[len] != ' ' && line[len] != '\t' && line[len] != '\n')
		len++;
	rgb_str = ft_split(ft_substr(line, j, len - j), ',');
	count = 0;
	while (rgb_str[count])
		count++;
	if (count != 3)
	{
		free_tab((void **)rgb_str);
		return (NULL);
	}
	rgb_num = malloc(sizeof(int) * 3);
	if (!rgb_num)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return (NULL);
	}
	return (rgb_atoi(rgb_str, rgb_num));
}

int	get_color_texture(t_game *game, t_map *map, char *line, int j)
{
	// F, C
	if (line[j + 1] && ft_isascii(line[j + 1]) && line[j + 1] != ' ' && line[j + 1] == '\t')
		return (err_msg(game->cubfile_name, ERR_FLOOR_CEILING, ERR));
	if (line[j] == 'F' && !map->floor_color)
	{
		map->floor_color = get_rgb(line, j + 1);
		if (!map->floor_color)
			return(err_msg(game->cubfile_name, ERR_FLOOR_CEILING, ERR));
	}
	else if (line[j] == 'C' && !map->ceiling_color)
	{
		map->ceiling_color = get_rgb(line, j + 1);
		if (!map->ceiling_color)
			return (err_msg(game->cubfile_name, ERR_FLOOR_CEILING, ERR));
	}
	else
		return (err_msg(game->cubfile_name, ERR_FLOOR_CEILING, ERR));
	return (SUCCESS);
}
