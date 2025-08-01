/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:16:40 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/01 15:10:19 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	assign_direction(t_player *p, int dir)
{
	if (dir == UP)
	{
		p->delta_x = PLAYERSPEED * p->cam_x;
		p->delta_y = PLAYERSPEED * p->cam_y;
	}
	else if (dir == DOWN)
	{
		p->delta_x = PLAYERSPEED * (-p->cam_y);
		p->delta_y = PLAYERSPEED * p->cam_x;
	}
	else if (dir == RIGHT)
	{
		p->delta_x = PLAYERSPEED * (-p->cam_x);
		p->delta_y = PLAYERSPEED * (-p->cam_y);
	}
	else
	{
		p->delta_x = PLAYERSPEED * p->cam_y;
		p->delta_y = PLAYERSPEED * (-p->cam_x);
	}
}

void	handle_y_wall(t_cube *cube, int pixel_move_y, int potential_y, int tile_y)
{
	cube->p.error_y -= pixel_move_y;
	cube->p.precise_y += cube->p.delta_y;
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

void	handle_x_wall(t_cube *cube, int pixel_move_x, int potential_x, int tile_x)
{
	cube->p.error_x -= pixel_move_x;
	cube->p.precise_x += cube->p.delta_x;
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

void	update_player_position(t_cube *cube, int dir)
{
	int potential_x;
	int	potential_y;
	int tile_x;
	int tile_y;
	int pixel_move_x;
	int pixel_move_y;
	
	assign_direction(&cube->p, dir);
	cube->p.error_x += cube->p.delta_x;
	cube->p.error_y += cube->p.delta_y;
	
	pixel_move_x = (int)cube->p.error_x;
	pixel_move_y = (int)cube->p.error_y;
	potential_x = 0;
	potential_y = 0;
	tile_x = 0;
	tile_y = 0;
	
	if (pixel_move_x != 0)
		handle_x_wall(cube, pixel_move_x, potential_x, tile_x);

	if (pixel_move_y != 0)
		handle_y_wall(cube, pixel_move_y, potential_y, tile_y);
}
