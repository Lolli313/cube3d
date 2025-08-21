/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:34:58 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/21 16:11:34 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	prepare_coords(t_cube *cube)
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

t_img	*check_wall_side_2(t_cube *cube)
{
	if (cube->coord.side == 1)
	{
		if (cube->coord.ray_dir_y > 0)
			return (cube->map.SO);
		else
			return (cube->map.NO);
	}
	else
	{
		if (cube->coord.ray_dir_x > 0)
			return (cube->map.EA);
		else
			return (cube->map.WE);
	}
}

void	check_wall_side(t_cube *cube, int *tex_height, int *tex_width)
{
	cube->coord.side_detailed = check_wall_side_2(cube);
	if (cube->coord.side_detailed == cube->map.SO)
	{
		*tex_height = cube->map.SO->height;
		*tex_width = cube->map.SO->width;
	}
	else if (cube->coord.side_detailed == cube->map.NO)
	{
		*tex_height = cube->map.NO->height;
		*tex_width = cube->map.NO->width;
	}
	else if (cube->coord.side_detailed == cube->map.WE)
	{
		*tex_height = cube->map.WE->height;
		*tex_width = cube->map.WE->width;
	}
	else
	{
		*tex_height = cube->map.EA->height;
		*tex_width = cube->map.EA->width;
	}
}

int	draw_line(t_cube *cube, int screen_x, int wall_height, int draw_start)
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		tex_height;
	int		tex_width;
	int		y;
	double	zoom_factor;
	double	effective_tex_height;
	double	tex_offset;

	check_wall_side(cube, &tex_height, &tex_width);
	if (cube->coord.side == 0)
		wall_x = cube->coord.start_y + cube->coord.perp_wall_dist * cube->coord.ray_dir_y;
	else
		wall_x = cube->coord.start_x + cube->coord.perp_wall_dist * cube->coord.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)(tex_width));
	if (cube->coord.side == 0 && cube->coord.ray_dir_x > 0)
		tex_x = tex_width - tex_x - 1;
	if (cube->coord.side == 1 && cube->coord.ray_dir_y < 0)
		tex_x = tex_width - tex_x - 1;
	
	if (cube->coord.perp_wall_dist < 1.0)
	{
		zoom_factor = 1.0 / cube->coord.perp_wall_dist;
		effective_tex_height = tex_height / zoom_factor;
		tex_offset = (tex_height - effective_tex_height) / 2.0;
		step = effective_tex_height / wall_height;
		tex_pos = tex_offset + (draw_start - HEIGHT / 2 + wall_height / 2) * step;
	}
	else
	{
		step = 1.0 * tex_height / wall_height;
		tex_pos = (draw_start - HEIGHT / 2 + wall_height / 2) * step;
	}
	y = 0;
	while (y < wall_height)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex_height)
			tex_y = tex_height - 1;
		tex_pos += step;
		cube->color = get_texture_pixel(cube->coord.side_detailed, tex_x, tex_y);
		draw_pixel(&cube->img, screen_x, draw_start, cube->color);
		draw_start++;
		y++;
	}
	return (1);
}

void	draw_wall(t_cube *cube, int screen_x)
{
    double	wall_height;
    int		wall_y;

    if (cube->coord.side == 0)
        cube->coord.perp_wall_dist = (cube->coord.map_x - cube->coord.start_x + (1 - cube->coord.step_x) / 2.0) / cube->coord.ray_dir_x;
    else
        cube->coord.perp_wall_dist = (cube->coord.map_y - cube->coord.start_y + (1 - cube->coord.step_y) / 2.0) / cube->coord.ray_dir_y;

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

