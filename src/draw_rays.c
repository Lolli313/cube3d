/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:34:58 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/29 15:39:56 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	prepare_coords_2(t_cube *cube, double pos_x, double pos_y)
{
	if (cube->coord.ray_dir_x < 0)
	{
		cube->coord.step_x = -1;
		cube->coord.side_dist_x = (pos_x - cube->coord.map_x)
			* cube->coord.delta_dist_x;
	}
	else
	{
		cube->coord.step_x = 1;
		cube->coord.side_dist_x = (cube->coord.map_x + 1.0 - pos_x)
			* cube->coord.delta_dist_x;
	}
	if (cube->coord.ray_dir_y < 0)
	{
		cube->coord.step_y = -1;
		cube->coord.side_dist_y = (pos_y - cube->coord.map_y)
			* cube->coord.delta_dist_y;
	}
	else
	{
		cube->coord.step_y = 1;
		cube->coord.side_dist_y = (cube->coord.map_y + 1.0 - pos_y)
			* cube->coord.delta_dist_y;
	}
}

void	prepare_coords(t_cube *cube)
{
	double	pos_x;
	double	pos_y;

	pos_x = cube->p.precise_x / TILESIZE;
	pos_y = cube->p.precise_y / TILESIZE;
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
	prepare_coords_2(cube, pos_x, pos_y);
}

void	draw_ray(t_cube *cube, int screen_x)
{
	prepare_coords(cube);
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
		if (cube->coord.map_x < 0 || cube->coord.map_x >= cube->map.width || 
			cube->coord.map_y < 0 || cube->coord.map_y >= cube->map.height)
			break ;
		if (cube->map.map[cube->coord.map_y][cube->coord.map_x] == 1)
			break ;
		else if (cube->map.map[cube->coord.map_y][cube->coord.map_x] == 3)
		{
			if (!is_door_open(cube))
				break ;
		}
	}
	if (!DEBUG)
		draw_wall(cube, screen_x);
}
