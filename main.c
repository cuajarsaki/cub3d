/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:56:48 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/31 23:14:03 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	main(void)
// {
// 	void	*mlx;

// 	mlx = mlx_init();
// 	mlx_new_window(mlx, 1920, 1080, "Hello world!");
// 	mlx_loop(mlx);
// }

void	print_tab(char **content)
{
	if (!content || !*content)
		return ;
	while (*content)
	{
		printf("%s\n", *content);
		content++;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_game	game;
	
	if (argc != 2)
		return (err_msg("Usage", ERR_USAGE, FAILURE));
	init_game(&game, argv[1]);
	if (parse_args(&game, argv) != 0)
		return (1);
	init_mlx_window(&game);
	init_player_direction(&game);
	render(&game);
	register_hook(&game);
	mlx_loop(game.mlx->mlx_ptr);
	// printf("========== game info ==========\n");
	// printf("game.textures[NORTH].path: %s\n", game.textures[NORTH].path);
	// printf("game.textures[SOUTH].path: %s\n", game.textures[SOUTH].path);
	// printf("game.textures[EAST].path: %s\n", game.textures[EAST].path);
	// printf("game.textures[WEST].path: %s\n", game.textures[WEST].path);
	// printf("game.map->floor_color: %X\n", game.map->floor_hex);
	// printf("game.map->ceiling_color: %X\n", game.map->ceiling_hex);
	// printf("game.map->height: %d\n", game.map->height);
	// printf("game.map->width: %d\n", game.map->width);
	// printf("========== game.map->grid ==========\n");
	// print_tab(game.map->grid);
	return (0);
}
