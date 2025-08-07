/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:16:40 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/07 16:35:09 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	assign_direction(t_player *p, int dir)
{
	p->cam_x = cos(p->player_direction);
	p->cam_y = sin(p->player_direction);
	if (dir == UP)
	{
		p->delta_x = PLAYERSPEED * p->cam_x;
		p->delta_y = PLAYERSPEED * p->cam_y;
	}
	else if (dir == RIGHT)
	{
		p->delta_x = PLAYERSPEED * (-p->cam_y);
		p->delta_y = PLAYERSPEED * p->cam_x;
	}
	else if (dir == DOWN)
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

void handle_y_wall(t_cube *cube, double new_precise_y)
{
	int potential_y;
	
	potential_y = (int)new_precise_y;
	if (cube->p.delta_y > 0)
	{
		if (check_wall_tile(cube, cube->p.position_x, potential_y, DOWN))
		{
			int tile_y = (potential_y + PLAYERSIZE) / (HEIGHT / MAP_Y);
			cube->p.precise_y = tile_y * (HEIGHT / MAP_Y) - PLAYERSIZE;
			cube->p.position_y = (int)cube->p.precise_y;
			return;
		}
	}
	else if (cube->p.delta_y < 0)
	{
		if (check_wall_tile(cube, cube->p.position_x, potential_y, UP))
		{
			int tile_y = potential_y / (HEIGHT / MAP_Y);
			cube->p.precise_y = (tile_y + 1) * (HEIGHT / MAP_Y);
			cube->p.position_y = (int)cube->p.precise_y;
			return;
		}
	}
	cube->p.precise_y = new_precise_y;
	cube->p.position_y = (int)cube->p.precise_y;
}

void handle_x_wall(t_cube *cube, double new_precise_x)
{
	int potential_x;
	
	potential_x = (int)new_precise_x;
	if (cube->p.delta_x > 0)
	{
		if (check_wall_tile(cube, potential_x, cube->p.position_y, RIGHT))
		{
			int tile_x = (potential_x + PLAYERSIZE) / (WIDTH / MAP_X);
			cube->p.precise_x = tile_x * (WIDTH / MAP_X) - PLAYERSIZE;
			cube->p.position_x = (int)cube->p.precise_x;
			return;
		}
	}
	else if (cube->p.delta_x < 0)
	{
		if (check_wall_tile(cube, potential_x, cube->p.position_y, LEFT))
		{
			int tile_x = potential_x / (WIDTH / MAP_X);
			cube->p.precise_x = (tile_x + 1) * (WIDTH / MAP_X);
			cube->p.position_x = (int)cube->p.precise_x;
			return;
		}
	}
	cube->p.precise_x = new_precise_x;
	cube->p.position_x = (int)cube->p.precise_x;
}

void update_player_position(t_cube *cube, int dir)
{
	double	new_precise_x;
	double	new_precise_y;
	
	assign_direction(&cube->p, dir);
	new_precise_x = cube->p.precise_x + cube->p.delta_x;
	handle_x_wall(cube, new_precise_x);
	new_precise_y = cube->p.precise_y + cube->p.delta_y;
	handle_y_wall(cube, new_precise_y);
}
