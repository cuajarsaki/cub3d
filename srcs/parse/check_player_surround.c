/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_surround.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:39:29 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/11 01:36:30 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	grid_floodfill(t_game *game, char **grid, int i, int j)
{
	if (i < 0 || game->map->height <= i || j < 0 || game->map->width <= j)
		return (FAILURE);
	if (grid[i][j] == '1')
		return (SUCCESS);
	if (grid[i][j] == 'V')
		return (SUCCESS);
	grid[i][j] = 'V';
	if (grid_floodfill(game, grid, i - 1, j) == FAILURE
		|| grid_floodfill(game, grid, i + 1, j) == FAILURE
		|| grid_floodfill(game, grid, i, j - 1) == FAILURE
		|| grid_floodfill(game, grid, i, j + 1) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	no_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f')
		return (FAILURE);
	return (SUCCESS);
}

static int	check_player_surround_helper(t_game *game, char **grid)
{
	int	i;
	int	j;
	
	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == game->map->start_dir)
			{
				if (i == 0 || i == game->map->height - 1 || j == 0 || j == game->map->width - 1)
					return (FAILURE);
				if (ft_strlen(grid[i - 1]) < (size_t)j || ft_strlen(grid[i + 1]) < (size_t)j)
					return (FAILURE);
				if (no_white_space(grid[i - 1][j]) == FAILURE
					|| no_white_space(grid[i + 1][j]) == FAILURE
					|| no_white_space(grid[i][j - 1]) == FAILURE
					|| no_white_space(grid[i][j + 1]) == FAILURE)
					return (FAILURE);
				grid[i][j] = '0';
				return (grid_floodfill(game, grid, i, j));
			}
			j++;
		}
		i++;
	}
	return (FAILURE);
}

static void	clean_visited(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == 'V')
				grid[i][j] = '0';
			j++;
		}
		i++;
	}
}

int	check_player_surround(t_game *game, char **grid)
{
	int			i;
	int			j;
	t_vector	*position;

	if (game->map->start_dir == '0') // todo: player　not foundではない？
		return (err_msg(game->cubfile_name, ERR_PLAYER_DIR, FAILURE));
	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (ft_strchr("NSEW", grid[i][j]) != NULL)
			{
				position = malloc(sizeof(t_vector));
				if (!position)
						return (err_msg(NULL, ERR_MALLOC, FAILURE));
				position->x = (double)j + 0.5;
				position->y = (double)i + 0.5; // todo: 0.5はなんで必要？
				game->player->pos = position;
			}
			j++;
		}
		i++;
	}
	if (check_player_surround_helper(game, grid) == FAILURE)
		return (err_msg(game->cubfile_name, ERR_PLAYER_POS, FAILURE));
	clean_visited(grid);
	return (SUCCESS);
}
