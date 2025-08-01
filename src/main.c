/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:00 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/01 14:45:02 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
	cos(θ - π/2) = sin(θ)
	sin(θ - π/2) = -cos(θ)
	cos(θ + π/2) = -sin(θ)
	sin(θ + π/2) = cos(θ)
*/

void	update_player_position(t_cube *cube, int dir)
{
	double delta_x, delta_y;
	int potential_x, potential_y;
	int tile_x, tile_y;
	
	if (dir == UP)
	{
		delta_x = PLAYERSPEED * cube->p.cam_x;
		delta_y = PLAYERSPEED * cube->p.cam_y;
	}
	else if (dir == DOWN)
	{
		delta_x = PLAYERSPEED * (-cube->p.cam_y);
		delta_y = PLAYERSPEED * cube->p.cam_x;
	}
	else if (dir == RIGHT)
	{
		delta_x = PLAYERSPEED * (-cube->p.cam_x);
		delta_y = PLAYERSPEED * (-cube->p.cam_y);
	}
	else
	{
		delta_x = PLAYERSPEED * cube->p.cam_y;
		delta_y = PLAYERSPEED * (-cube->p.cam_x);
	}
	
	cube->p.error_x += delta_x;
	cube->p.error_y += delta_y;
	
	int pixel_move_x = (int)cube->p.error_x;
	int pixel_move_y = (int)cube->p.error_y;
	
	if (pixel_move_x != 0)
	{
		cube->p.error_x -= pixel_move_x;
		cube->p.precise_x += delta_x;
		potential_x = (int)cube->p.precise_x;
		
		if (pixel_move_x > 0)
		{
			if (check_wall_tile(cube, potential_x, cube->p.position_y, RIGHT))
			{
				tile_x = (potential_x + PLAYERSIZE) / (WIDTH / MAP_X);
				cube->p.precise_x = tile_x * (WIDTH / MAP_X) - PLAYERSIZE;
			}
		}
		else
		{
			if (check_wall_tile(cube, potential_x, cube->p.position_y, LEFT))
			{
				tile_x = potential_x / (WIDTH / MAP_X);
				cube->p.precise_x = (tile_x + 1) * (WIDTH / MAP_X);
			}
		}
		cube->p.position_x = (int)cube->p.precise_x;
	}
	
	if (pixel_move_y != 0)
	{
		cube->p.error_y -= pixel_move_y;
		cube->p.precise_y += delta_y;
		potential_y = (int)cube->p.precise_y;
		
		if (pixel_move_y > 0)
		{
			if (check_wall_tile(cube, cube->p.position_x, potential_y, DOWN))
			{
				tile_y = (potential_y + PLAYERSIZE) / (HEIGHT / MAP_Y);
				cube->p.precise_y = tile_y * (HEIGHT / MAP_Y) - PLAYERSIZE;
			}
		}
		else
		{
			if (check_wall_tile(cube, cube->p.position_x, potential_y, UP))
			{
				tile_y = potential_y / (HEIGHT / MAP_Y);
				cube->p.precise_y = (tile_y + 1) * (HEIGHT / MAP_Y);
			}
		}
		cube->p.position_y = (int)cube->p.precise_y;
	}
}

int	main(int ac, char **av)
{
	t_cube cube;

	(void)ac;
	(void)av;
	init_cube(&cube);
	init_keys(&cube);
	init_hooks(&cube);
	init_image(&cube);
	render_image(&cube);
	mlx_loop(cube.mlx);
}