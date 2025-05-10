/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:43:40 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/10 23:49:08 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && line[len] != ' ' && line[len] != '\t') // todo: !='\n'はいらないの？
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
		path[i++] = line[j++];
	path[i] = '\0';
	// 改行で区切られてるかチェック
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

static int	get_direction_texture(t_texinfo *textures, char *line, int j)
{
	if (line[j + 2] && (ft_isascii(line[j + 2]) && line[j + 2] != ' ' && line[j + 2] != '\t'))
		return (ERR);
	if (line[j] == 'N' && line[j + 1] == 'O' && (textures[NORTH]).path == NULL)
		(textures[NORTH]).path = get_texture_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && (textures[SOUTH]).path == NULL)
		(textures[SOUTH]).path = get_texture_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && (textures[EAST]).path == NULL)
		(textures[EAST]).path = get_texture_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && (textures[WEST]).path == NULL)
		(textures[WEST]).path = get_texture_path(line, j + 2);
	else
		return (ERR);
	return(SUCCESS);
}

static int	get_info(t_game *game, char **content, int i, int j)
{
	int	tmp;

	if (content[i][j] == '\n')
		return (BREAK);
	while (content[i][j] == ' ' || content[i][j] == '\t')
		j++;
	// map以外
	if (ft_isascii(content[i][j]) && !ft_isdigit(content[i][j]))
	{
		tmp = j + 1;
		while (content[i][tmp] != ' ' && content[i][tmp] != '\t')
			tmp++;
		while (content[i][tmp] == ' ' || content[i][tmp] == '\t')
			tmp++;
		// NO, SO, EA, WE
		if (content[i][tmp] && ft_isascii(content[i][tmp]) && !ft_isdigit(content[i][tmp]))
		{
			if (get_direction_texture(game->textures, content[i], j) == ERR)
				return (err_msg(game->cubfile_name, ERR_TEX_INVAILD, FAILURE));
			return (BREAK);
		}
		// C, F
		else
		{
			if (get_color_texture(game, game->map, content[i], j) == ERR)
				return (FAILURE);
			return (BREAK);
		}
	}
	// map
	else if (ft_isdigit(content[i][j]))
	{
		if (!game->map->floor_color || !game->map->ceiling_color
			|| !game->textures[NORTH].path || !game->textures[SOUTH].path
			|| !game->textures[EAST].path || !game->textures[WEST].path)
			return (err_msg(game->cubfile_name, ERR_MAP_END, FAILURE));
		if (get_map(game, content, i) == FAILURE)
			return (err_msg(game->cubfile_name, ERR_INVALID_MAP, FAILURE));
		return (SUCCESS);
	}
	return (CONTINUE);
}

int	get_file_data(t_game *game, char **content)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (content[i])
	{
		j = 0;
		while (content[i][j])
		{
			ret = get_info(game, content, i, j);
			if (ret == BREAK)
				break ;
			else if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
