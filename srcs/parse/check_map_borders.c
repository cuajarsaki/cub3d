/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_borders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:17:39 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/10 19:29:32 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_top_or_bottom(char **grid, int i, int j)
{
	if (!grid || !grid[i] || !grid[i][j])
		return (FAILURE);
	while (grid[i][j] == ' ' || grid[i][j] == '\t' || grid[i][j] == '\r'
		|| grid[i][j] == '\v' || grid[i][j] == '\f')
		j++;
	while (grid[i][j])
	{
		if (grid[i][j] != '1') // todo: space, tabどうする？ →スペース埋めたから不要!?
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	check_map_borders(t_map *map, char **grid)
{
	int	i;
	int	j;

	// top
	if (check_top_or_bottom(grid, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < map->height - 1)
	{
		// grid作るときに左端の1は確認済みのため、右端のみチェック
		j = ft_strlen(grid[i]) - 1;
		if (grid[i][j] != '1')
			return (FAILURE);
		i++;
	}
	// bottom
	if (check_top_or_bottom(grid, i, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
