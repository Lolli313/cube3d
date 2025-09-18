/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:17:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/18 16:44:20 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_line_3(t_cube *cube, int screen_x, int wall_height,
							int draw_start)
{
	int	y;

	y = 0;
	while (y < wall_height)
	{
		cube->tex.tex_y = (int)cube->tex.tex_pos;
		if (cube->tex.tex_y < 0)
			cube->tex.tex_y = 0;
		if (cube->tex.tex_y >= cube->tex.tex_height)
			cube->tex.tex_y = cube->tex.tex_height - 1;
		cube->tex.tex_pos += cube->tex.step;
		cube->color = get_texture_pixel(cube->coord.side_detailed,
				cube->tex.tex_x, cube->tex.tex_y);
		draw_pixel(&cube->img, screen_x, draw_start, cube->color);
		draw_start++;
		y++;
	}
}

static void	draw_line_2(t_cube *cube, int wall_height, int draw_start)
{
	double	zoom_factor;

	if (cube->coord.perp_wall_dist < 1.0)
	{
		zoom_factor = 1.0 / cube->coord.perp_wall_dist;
		cube->tex.visual_tex_height = cube->tex.tex_height / zoom_factor;
		cube->tex.tex_offset = (cube->tex.tex_height
				- cube->tex.visual_tex_height) / 2.0;
		cube->tex.step = cube->tex.visual_tex_height / wall_height;
		cube->tex.tex_pos = cube->tex.tex_offset + (draw_start - HEIGHT / 2
				+ wall_height / 2) * cube->tex.step;
	}
	else
	{
		cube->tex.step = 1.0 * cube->tex.tex_height / wall_height;
		cube->tex.tex_pos = (draw_start - HEIGHT / 2 + wall_height / 2)
			* cube->tex.step;
	}
}

static void	draw_line(t_cube *cube, int screen_x, int wall_height, int wall_y)
{
	double	wall_x;

	check_wall_side(cube, &cube->tex.tex_height, &cube->tex.tex_width);
	if (cube->coord.side == 0)
		wall_x = cube->coord.start_y + cube->coord.perp_wall_dist
			* cube->coord.ray_dir_y;
	else
		wall_x = cube->coord.start_x + cube->coord.perp_wall_dist
			* cube->coord.ray_dir_x;
	wall_x -= floor(wall_x);
	cube->tex.tex_x = (int)(wall_x * (double)(cube->tex.tex_width));
	if (cube->coord.side == 0 && cube->coord.ray_dir_x > 0)
		cube->tex.tex_x = cube->tex.tex_width - cube->tex.tex_x - 1;
	if (cube->coord.side == 1 && cube->coord.ray_dir_y < 0)
		cube->tex.tex_x = cube->tex.tex_width - cube->tex.tex_x - 1;
	draw_line_2(cube, wall_height, wall_y);
	draw_line_3(cube, screen_x, wall_height, wall_y);
}

void	draw_wall(t_cube *cube, int screen_x)
{
	double	wall_height;
	int		wall_y;

	if (cube->coord.side == 0)
		cube->coord.perp_wall_dist = (cube->coord.map_x - cube->coord.start_x
				+ (1 - cube->coord.step_x) / 2.0) / cube->coord.ray_dir_x;
	else
		cube->coord.perp_wall_dist = (cube->coord.map_y - cube->coord.start_y
				+ (1 - cube->coord.step_y) / 2.0) / cube->coord.ray_dir_y;
	if (cube->coord.perp_wall_dist < 0.001)
		cube->coord.perp_wall_dist = 0.001;
	wall_height = HEIGHT / cube->coord.perp_wall_dist;
	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
	wall_y = (HEIGHT / 2) - (wall_height / 2);
	draw_line(cube, screen_x, wall_height, wall_y);
}
