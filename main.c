/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:56:48 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/09 18:21:27 by rhonda           ###   ########.fr       */
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
		printf("%s", *content);
		content++;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_game	game;
	
	if (argc != 2)
		return (err_msg("Usage", ERR_USAGE, FAILURE));
	init_game(&game);
	if (parse_args(&game, argv) != 0)
		return (1);
	print_tab(game.content);
	return (0);
}
