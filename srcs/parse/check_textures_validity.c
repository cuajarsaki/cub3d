/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_validity.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:38:33 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/10 19:05:46 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_rgb_validity(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || 255 < rgb[i])
			return (err_msg_int(rgb[i], ERR_TEX_RGB_VAL, FAILURE));
		i++;
	}
	return (SUCCESS);
}

static	unsigned int	rgb_to_hex(int *rgb_tab)
{
	unsigned int	hex;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	// 0xff = 256とAND演算で、下位8ビットのみを取得
	hex = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (hex);
}

int	check_textures_validity(t_game *game, t_texinfo *textures, t_map *map)
{
	if (!textures[NORTH].path || !textures[SOUTH].path
		|| !textures[EAST].path || !textures[WEST].path)
		return (err_msg(game->cubfile_name, ERR_TEX_MISSING, FAILURE));
	if (!map->floor_color || !map->ceiling_color)
		return (err_msg(game->cubfile_name, ERR_COLOR_MISSING, FAILURE));
	if (check_file_type(textures[NORTH].path, XPM) == FAILURE
		|| check_file_type(textures[SOUTH].path, XPM) == FAILURE
		|| check_file_type(textures[EAST].path, XPM) == FAILURE
		|| check_file_type(textures[WEST].path, XPM) == FAILURE
		|| check_rgb_validity(map->floor_color) == FAILURE
		|| check_rgb_validity(map->ceiling_color) == FAILURE)
		return (FAILURE);
	map->floor_hex = rgb_to_hex(map->floor_color);
	map->ceiling_hex = rgb_to_hex(map->ceiling_color);
	return (SUCCESS);
}
