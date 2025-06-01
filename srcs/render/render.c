/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:54:44 by rhonda            #+#    #+#             */
/*   Updated: 2025/06/01 17:30:27 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_player_direction(t_game *game)
{
	// init player->plane
	game->player->plane = malloc(sizeof(t_vector));
	if (!game->player->plane)
		return (err_msg(NULL, ERR_MALLOC, FAILURE));
		
	// init player->dir
	game->player->dir = malloc(sizeof(t_vector));
	if (!game->player->dir)
		return (err_msg(NULL, ERR_MALLOC, FAILURE));
	if (game->map->start_dir == 'N')
	{
		game->player->dir->x = 0;
		game->player->dir->y = -1;
		game->player->plane->x = FOV;
		game->player->plane->y = 0;
	}
	else if (game->map->start_dir == 'S')
	{
		game->player->dir->x = 0;
		game->player->dir->y = 1;
		game->player->plane->x = -FOV;
		game->player->plane->y = 0;
	}
	else if (game->map->start_dir == 'E')
	{
		game->player->dir->x = 1;
		game->player->dir->y = 0;
		game->player->plane->x = 0;
		game->player->plane->y = FOV;
	}
	else if (game->map->start_dir == 'W')
	{
		game->player->dir->x = -1;
		game->player->dir->y = 0;
		game->player->plane->x = 0;
		game->player->plane->y = -FOV;
	}
	else // error
	{
		game->player->dir->x = 0;
		game->player->dir->y = 0;
		game->player->plane->x = 0;
		game->player->plane->y = 0;
	}
	return (0);
}

int	render(t_game *game)
{	
	// render の一番上で
	mlx_clear_window(game->mlx->mlx_ptr, game->mlx->win_ptr);

	// raycasting loop
	// while (1)
	// {
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			// init ray
			t_ray ray;
			
			// printf("player.pos = (%f, %f)\n", game->player->pos->x, game->player->pos->y);
			
			// calculate ray position and direction
			double cameraX = 2.0 * x / WINDOW_WIDTH - 1.0;
			ray.dir.x = game->player->dir->x + game->player->plane->x * cameraX;
			ray.dir.y = game->player->dir->y + game->player->plane->y * cameraX;

			// whilch box of the map we are in
			ray.map_x = (int)game->player->pos->x;
			ray.map_y = (int)game->player->pos->y;

			// length of ray from one side to next side (x or y)
			// !!!! fisheye補正はここで既に行なっている
			ray.delta_dist.x = (ray.dir.x == 0) ? 1e30 : fabs(1 / ray.dir.x);
			ray.delta_dist.y = (ray.dir.y == 0) ? 1e30 : fabs(1 / ray.dir.y);

			ray.hit = false;

			// calculate step and initial sideDist;
			if (ray.dir.x < 0)
			{
				ray.step_x = -1;
				ray.side_dist.x = ray.delta_dist.x * (game->player->pos->x - ray.map_x);
			}
			else
			{
				ray.step_x = 1;
				ray.side_dist.x = ray.delta_dist.x * (ray.map_x + 1.0 - game->player->pos->x);
			}
			if (ray.dir.y < 0)
			{
				ray.step_y = -1;
				ray.side_dist.y = ray.delta_dist.y * (game->player->pos->y - ray.map_y);
			}
			else
			{
				ray.step_y = 1;
				ray.side_dist.y = ray.delta_dist.y * (ray.map_y + 1.0 - game->player->pos->y);
			}

			// perform DDA
			while (ray.hit == false)
			{
				if (ray.side_dist.x < ray.side_dist.y)
				{
					ray.side_dist.x += ray.delta_dist.x;
					ray.map_x += ray.step_x;
					ray.side = X;
				}
				else
				{
					ray.side_dist.y += ray.delta_dist.y;
					ray.map_y += ray.step_y;
					ray.side = Y;
				}
				if (game->map->grid[ray.map_y][ray.map_x] == '1')
					ray.hit = true;
			}

			// calculate perpWallDist
			if (ray.side == X)
				ray.perp_wall_dist = ray.side_dist.x - ray.delta_dist.x;
			else
				ray.perp_wall_dist = ray.side_dist.y - ray.delta_dist.y;
			
			// if (ray.side == X)
			// 	printf("ray.side X: dist = %f, sideX = %f, deltaX = %f\n", ray.perp_wall_dist, ray.side_dist.x, ray.delta_dist.x);
			// else
			// 	printf("ray.side Y: dist = %f, sideY = %f, deltaY = %f\n", ray.perp_wall_dist, ray.side_dist.y, ray.delta_dist.y);

			
			// calculate height of line to draw on screen
			// !!!! 逆数を取ることで距離が近いほど大きく、遠いほど小さくなる
			ray.line_height = (int)(WINDOW_HEIGHT / ray.perp_wall_dist);
			
			// calculate lowest and highest pixel
			ray.draw_start = (-ray.line_height + WINDOW_HEIGHT) / 2;
			if (ray.draw_start < 0)
				ray.draw_start = 0;
			ray.draw_end = (ray.line_height + WINDOW_HEIGHT) / 2;
			if (ray.draw_end >= WINDOW_HEIGHT)
				ray.draw_end = WINDOW_HEIGHT - 1;
			
			// color
			int	color = 0;
			if (ray.side == X)
			{
				if (ray.step_x > 0)
					color = 0xB4B4FF; // East (purple)
				else
					color = 0xB4FFB4; // West (green)
			}
			else
			{
				if (ray.step_y > 0)
					color = 0xFFB4B4; // South (red)
				else
					color = 0xB4FFFF; // North (cyan)
			}
			
			if (ray.side == Y)
				color /= 2;
			
			
			// render
			for (int y = 0; y < ray.draw_start; y++)
			{
				mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x, y, game->map->ceiling_hex);
			}
			for (int y = ray.draw_start; y < ray.draw_end; y++)
			{
				mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x, y, color);
			}
			for (int y = ray.draw_end; y < WINDOW_HEIGHT; y++)
			{
				mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x, y, game->map->floor_hex);
			}
		
			// // debug
			// if (x % 100 == 0)
			// 	printf("x = %d, cameraX = %f, rayDir = (%f, %f)\n", x, cameraX, ray.dir.x, ray.dir.y);
			// if (x % 100 == 0)
			// 	printf("x = %d, perpWallDist = %.2f, lineHeight = %d\n", x, ray.perp_wall_dist, ray.line_height);
			// if (x % 100 == 0)
			// {
			// 	printf("x = %d, side = %d, step_x = %d, step_y = %d\n",
			// 		x, ray.side, ray.step_x, ray.step_y);
			// }
		}
	// }
	return (0);
}
