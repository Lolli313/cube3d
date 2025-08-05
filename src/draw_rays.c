/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:34:58 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/05 16:58:52 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	prepare_coords(t_cube *cube, double angle)
{
	double	pos_x;
	double	pos_y;
	
	cube->coord.ray_dir_x = cos(angle);
	cube->coord.ray_dir_y = sin(angle);

	pos_x = (cube->p.precise_x + (PLAYERSIZE / 2.0)) / (WIDTH / (double)MAP_X);
	pos_y = (cube->p.precise_y + (PLAYERSIZE / 2.0)) / (HEIGHT / (double)MAP_Y);

	cube->coord.start_x = pos_x;
	cube->coord.start_y = pos_y;
	cube->coord.map_x = (int)pos_x;
	cube->coord.map_y = (int)pos_y;

	if (cube->coord.ray_dir_x == 0)
		cube->coord.delta_dist_x = INFINITY;
	else
		cube->coord.delta_dist_x = fabs(1.0 / cube->coord.ray_dir_x);
	if (cube->coord.ray_dir_y == 0)
		cube->coord.delta_dist_y = INFINITY;
	else
		cube->coord.delta_dist_y = fabs(1.0 / cube->coord.ray_dir_y);

	if (cube->coord.ray_dir_x < 0)
	{
		cube->coord.step_x = -1;
		cube->coord.side_dist_x = (pos_x - cube->coord.map_x) * cube->coord.delta_dist_x;
	}
	else
	{
		cube->coord.step_x = 1;
		cube->coord.side_dist_x = (cube->coord.map_x + 1.0 - pos_x) * cube->coord.delta_dist_x;
	}
	if (cube->coord.ray_dir_y < 0)
	{
		cube->coord.step_y = -1;
		cube->coord.side_dist_y = (pos_y - cube->coord.map_y) * cube->coord.delta_dist_y;
	}
	else
	{
		cube->coord.step_y = 1;
		cube->coord.side_dist_y = (cube->coord.map_y + 1.0 - pos_y) * cube->coord.delta_dist_y;
	}
}

void	draw_wall(t_cube *cube, int screen_x)
{
	double perp_wall_dist;
	double wall_height;
	int temp_height;
	int wall_y;
	
	cube->color = DARK_GREEN;
	temp_height = 0;
	if (cube->coord.side == 0)
		perp_wall_dist = (cube->coord.side_dist_x - cube->coord.delta_dist_x);
	else
		perp_wall_dist = (cube->coord.side_dist_y - cube->coord.delta_dist_y);
	if (perp_wall_dist < 0.001)
		perp_wall_dist = 0.001;
	wall_height = HEIGHT / perp_wall_dist;
	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
	wall_y = (HEIGHT / 2) - (wall_height / 2);
	if (cube->coord.side == 1)
		cube->color = GREEN;
	while (temp_height < wall_height)
	{
		draw_pixel(&cube->img, screen_x, wall_y, cube->color);
		temp_height++;
		wall_y++;
	}
}

void	draw_ray(t_cube *cube, double angle, int screen_x)
{
	prepare_coords(cube, angle);
	while (1)
	{
		if (cube->coord.side_dist_x < cube->coord.side_dist_y)
		{
			cube->coord.side_dist_x += cube->coord.delta_dist_x;
			cube->coord.map_x += cube->coord.step_x;
			cube->coord.side = 0;
		}
		else
		{
			cube->coord.side_dist_y += cube->coord.delta_dist_y;
			cube->coord.map_y += cube->coord.step_y;
			cube->coord.side = 1;
		}
		if (cube->map.map[cube->coord.map_y][cube->coord.map_x] == 1)
			break;
	}
	if (!DEBUG)
		draw_wall(cube, screen_x);
}

