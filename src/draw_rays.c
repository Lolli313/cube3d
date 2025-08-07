/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:34:58 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/07 16:27:18 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	prepare_coords(t_cube *cube)
{
	double	pos_x;
	double	pos_y;

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

int	draw_line(t_cube *cube, int screen_x, int wall_height, int draw_start)
{
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_height;
	int		tex_width;
	int		y;

	tex_height = cube->map.SO->height;
	tex_width = cube->map.SO->width;

	if (cube->coord.side == 0)
		wall_x = cube->coord.start_y + cube->coord.perp_wall_dist * cube->coord.ray_dir_y;
	else
		wall_x = cube->coord.start_x + cube->coord.perp_wall_dist * cube->coord.ray_dir_x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * tex_width);
	if (cube->coord.side == 0 && cube->coord.ray_dir_x > 0)
		tex_x = tex_width - tex_x - 1;
	if (cube->coord.side == 1 && cube->coord.ray_dir_y < 0)
		tex_x = tex_width - tex_x - 1;
	step = 1.0 * tex_height / wall_height;
	tex_pos = (draw_start - HEIGHT / 2 + wall_height / 2) * step;
	y = 0;
	while (y < wall_height)
	{
		int	tex_y = (int)tex_pos;
		tex_pos += step;
		cube->color = get_texture_pixel(cube->map.SO, tex_x, tex_y);
		draw_pixel(&cube->img, screen_x, draw_start, cube->color);
		draw_start++;
		y++;
	}
	return (1);
}

void	draw_wall(t_cube *cube, int screen_x)
{
	double	wall_height;
	int		temp_height;
	int		wall_y;
	
	temp_height = 0;
	if (cube->coord.side == 0)
		cube->coord.perp_wall_dist = (cube->coord.side_dist_x - cube->coord.delta_dist_x);
	else
		cube->coord.perp_wall_dist = (cube->coord.side_dist_y - cube->coord.delta_dist_y);
	if (cube->coord.perp_wall_dist < 0.001)
		cube->coord.perp_wall_dist = 0.001;
	wall_height = HEIGHT / cube->coord.perp_wall_dist;
	if (wall_height > HEIGHT)
		wall_height = HEIGHT; 
	wall_y = (HEIGHT / 2) - (wall_height / 2);
	draw_line(cube, screen_x, wall_height, wall_y);
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
		if (cube->map.map[cube->coord.map_y][cube->coord.map_x] == 1)
			break;
	}
	if (!DEBUG)
		draw_wall(cube, screen_x);
}

