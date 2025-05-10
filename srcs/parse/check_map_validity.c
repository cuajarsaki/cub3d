/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:09:47 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/11 01:40:24 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_elements(t_game *game, char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			while (grid[i][j] == ' ' || grid[i][j] == '\t' || grid[i][j] == '\r'
				|| grid[i][j] == '\v' || grid[i][j] == '\f')
				j++;
			if (ft_strchr("10NSEW", grid[i][j]) == NULL)
				return (err_msg(game->cubfile_name, ERR_INV_CHAR, FAILURE));
			if (game->map->start_dir != '0' && ft_strchr("NSEW", grid[i][j]) != NULL)
				return (err_msg(game->cubfile_name, ERR_NUM_PLAYER, FAILURE));
			if (game->map->start_dir == '0' && ft_strchr("NSEW", grid[i][j]) != NULL)
				game->map->start_dir = grid[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_map_validity(t_game *game, t_map *map)
{
	if (!map->grid)
		return (err_msg(game->cubfile_name, ERR_MAP_MISSING, FAILURE));
	if (check_map_borders(map, map->grid) == FAILURE)
		return (err_msg(game->cubfile_name, ERR_MAP_NO_CLOSED, FAILURE));
	if (map->height < 3)
		return (err_msg(game->cubfile_name, ERR_MAP_TOO_SMALL, FAILURE));
	if (check_map_elements(game, map->grid) == FAILURE)
		return (FAILURE);
	if (check_player_surround(game, map->grid) == FAILURE)
		return (FAILURE);
	// if (check_map_is_at_the_end(map->grid) == FAILURE) // todo: 別で対応してるから不要？
	// 	return (err_msg(game->cubfile_name, ERR_MAP_END, FAILURE));
	return (SUCCESS);
}
