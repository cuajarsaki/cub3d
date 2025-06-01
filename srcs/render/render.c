/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:54:44 by rhonda            #+#    #+#             */
/*   Updated: 2025/06/01 22:53:51 by rhonda           ###   ########.fr       */
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

	// raycasting loop　（one loopすると縦１列の線が描画できる）
	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		// init ray
		t_ray ray;
		
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
		
		// 壁に衝突したか判定フラグ
		ray.hit = false;

		// calculate step and initial sideDist
		// calculate x
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
		// calculate y
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
			// side_distはrayの累積の長さ
			// delta_distは１マス分進んだ時に伸びるrayの長さで、固定値
			// 壁にぶつかるまで、side_distをdelta_distずつ伸ばしていく
			// x, yのside_distを比較してより短い方を採用　　-> 採用された方のdelta_distをside_distに足す　-> 壁でなければ再度比較する
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
			// 壁に衝突したらフラグをtrueに
			if (game->map->grid[ray.map_y][ray.map_x] == '1')
				ray.hit = true;
		}

		// calculate perpWallDist (= 最終的な壁までの長さ)
		// 壁の中に突っ込んでいるため、１マス分減らす
		if (ray.side == X)
			ray.perp_wall_dist = ray.side_dist.x - ray.delta_dist.x;
		else
			ray.perp_wall_dist = ray.side_dist.y - ray.delta_dist.y;

			
		// calculate height of line to draw on screen
		// !!!! 逆数を取ることで距離が近いほど大きく、遠いほど小さくなる
		ray.line_height = (int)(WINDOW_HEIGHT / ray.perp_wall_dist);
			
		// calculate lowest and highest pixel
		// calculate start
		ray.draw_start = (-ray.line_height + WINDOW_HEIGHT) / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		// calculate end
		ray.draw_end = (ray.line_height + WINDOW_HEIGHT) / 2;
		if (ray.draw_end >= WINDOW_HEIGHT)
			ray.draw_end = WINDOW_HEIGHT - 1;
		
		// color　（todo: 今は固定値にしているため、実際のtextureに修正の必要あり）
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
		
		// yにぶつかったら少し明るくして、xとの差を作っている
		if (ray.side == Y)
			color /= 2;
		
		// render
		// ceiling
		for (int y = 0; y < ray.draw_start; y++)
		{
			mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x, y, game->map->ceiling_hex);
		}
		// wall　（todo: 引数colorは、対応するtextureのpixelに変更する必要あり）
		for (int y = ray.draw_start; y < ray.draw_end; y++)
		{
			mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x, y, color);
		}
		// floor
		for (int y = ray.draw_end; y < WINDOW_HEIGHT; y++)
		{
			mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x, y, game->map->floor_hex);
		}
	}
	return (0);
}

// root@cub3d:/workspace# ./cub3D assets/maps/test.cub
// X: 0.555556, Y: 1.500000, side: 1
// X: 1.666667, Y: 1.500000, side: 0
// X: 1.666667, Y: 2.500000, side: 1
// X: 2.777778, Y: 2.500000, side: 0
// X: 2.777778, Y: 3.500000, side: 1
// X: 3.888889, Y: 3.500000, side: 0
