/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:34:58 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/16 16:53:32 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	prepare_coords_2(t_cube *cube, double pos_x, double pos_y)
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

static void	prepare_coords(t_cube *cube)
{
	double	pos_x;
	double	pos_y;

	pos_x = (cube->p.precise_x + (PLAYERSIZE / 2.0)) / TILESIZE;
	pos_y = (cube->p.precise_y + (PLAYERSIZE / 2.0)) / TILESIZE;
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

static bool	check_door(t_cube *cube)
{
	if (cube->map.map[cube->coord.map_y][cube->coord.map_x] == 3
				&& !is_door_open(cube))
		return (true);
	return (false);
}

static bool	check_wall(t_cube *cube)
{
	if (cube->map.map[cube->coord.map_y][cube->coord.map_x] == 1
			|| cube->map.map[cube->coord.map_y][cube->coord.map_x] == 5)
	{
		cube->someyt.is_anim_wall = false;
		return (true);
	}
	else if (cube->map.map[cube->coord.map_y][cube->coord.map_x] == 6)
	{
		cube->someyt.is_anim_wall = true;
		return (true);
	}
	return (false);
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
		if (cube->coord.map_x < 0 || cube->coord.map_x >= cube->map.width
			|| cube->coord.map_y < 0 || cube->coord.map_y >= cube->map.height)
			break ;
		if (check_wall(cube))
			break ;
		else if (check_door(cube))
			break ;
	}
	draw_wall(cube, screen_x);
}
