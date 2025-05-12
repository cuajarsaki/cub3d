/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:39:08 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/10 02:03:17 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_lines(char **content, int i)
{
	int	start_index;
	int	j;

	start_index = i;
	while (content[i])
	{
		j = 0;
		while (content[i][j] == ' ' || content[i][j] == '\t' || content[i][j] == '\r'
			|| content[i][j] == '\v' || content[i][j] == '\f')
			j++;
		if (content[i][j] != '1') // 左端が1ならマップが続いている判定
			break ;
		i++;
	}
	return (i - start_index);
}

static size_t	find_longest_width(char **content, int index)
{
	size_t	longest;

	longest = ft_strlen(content[index]);
	while (content[index])
	{
		if (longest < ft_strlen(content[index]))
			longest = ft_strlen(content[index]);
		index++;
	}
	return (longest);
}

static int	fill_map_tab(t_map *map, char **content, int index)
{
	int	i;
	int	j;

	map->width = find_longest_width(content, index);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		map->grid[i] = malloc(sizeof(char) * (map->width + 1));
		if (!map->grid[i])
			return (err_msg(NULL, ERR_MALLOC, FAILURE));
		while (content[index][j] && content[index][j] != '\n')
		{
			map->grid[i][j] = content[index][j];
			j++;
		}
		while (j < map->width) // 左詰めでいいの？
		{
			map->grid[i][j] = '\0';
			j++;
		}
		index++;
		i++;
	}
	map->grid[i] = NULL;
	return (SUCCESS);
}

static int	get_map_helper(t_map *map, char **content, int i)
{
	map->height = count_map_lines(content, i);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (err_msg(NULL, ERR_MALLOC, FAILURE)); // todo: mallocは0じゃなかった？
	if (fill_map_tab(map, content, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	change_space_into_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j] == ' ' || map->grid[i][j] == '\t' || map->grid[i][j] == '\r'
			|| map->grid[i][j] == '\v' || map->grid[i][j] == '\f')
			j++;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == ' ') // todo:謎条件あり
				map->grid[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	get_map(t_game *game, char **content, int i)
{
	if (get_map_helper(game->map, content, i) == FAILURE)
		return (FAILURE);
	change_space_into_wall(game->map);
	return (SUCCESS);
}
