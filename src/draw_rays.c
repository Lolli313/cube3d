/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:34:58 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/02 17:53:37 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	prepare_coords(t_cube *cube, double angle)
{
	double ray_dir_x, ray_dir_y;
	double cos_angle, sin_angle;
	
	cube->coord.start_x = (int)cube->p.precise_x + (PLAYERSIZE / 2);
	cube->coord.start_y = (int)cube->p.precise_y + (PLAYERSIZE / 2);
	
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	
	ray_dir_x = cube->p.cam_x * cos_angle - cube->p.cam_y * sin_angle;
	ray_dir_y = cube->p.cam_x * sin_angle + cube->p.cam_y * cos_angle;
	
	cube->coord.end_x = cube->coord.start_x + (PLAYERDIRECTIONSIZE * ray_dir_x);
	cube->coord.end_y = cube->coord.start_y + (PLAYERDIRECTIONSIZE * ray_dir_y);
	
	cube->coord.dx = abs(cube->coord.end_x - cube->coord.start_x);
	cube->coord.dy = abs(cube->coord.end_y - cube->coord.start_y);
	if (cube->coord.start_x <= cube->coord.end_x)
		cube->coord.dir_x = 1;
	else
		cube->coord.dir_x = -1;
	if (cube->coord.start_y <= cube->coord.end_y)
		cube->coord.dir_y = 1;
	else
		cube->coord.dir_y = -1;
	if (cube->coord.dx > cube->coord.dy)
		cube->coord.err = cube->coord.dx / 2;
	else
		cube->coord.err = -cube->coord.dy / 2;
}

void	draw_wall(t_cube *cube, int x, int y, int screen_x, double angle)
{
	double	dx;
	double	dy;
	double	wall_height;
	double	corrected_distance;
	int		temp_height;
	int		wall_y;

	temp_height = 0;
	dx = abs(x - cube->coord.start_x);
	dy = abs(y - cube->coord.start_y);
	cube->p.height = sqrt(pow(dx, 2) + pow(dy, 2));
	corrected_distance = cube->p.height * cos(angle);
	if (corrected_distance <= 0.001)
		corrected_distance = 0.001;
	wall_height = HEIGHT * 100 / corrected_distance;
	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
	wall_y = (HEIGHT / 2) - (wall_height / 2);
	while (temp_height < wall_height)
	{
		draw_pixel(&cube->img, screen_x, wall_y, GREEN);
		temp_height++;
		wall_y++;
	}
}

void	draw_line(t_cube *cube, double angle, int screen_x)
{
	int	tile_x;
	int	tile_y;
	int	x;
	int	y;
	
	prepare_coords(cube, angle);
	x = cube->coord.start_x;
	y = cube->coord.start_y;
	while (1)
	{
		tile_x = x / (WIDTH / MAP_X);
		tile_y = y / (HEIGHT / MAP_Y);
		if (cube->map.map[tile_y][tile_x] == 1)
		{
			if (!DEBUG)
				draw_wall(cube, x, y, screen_x, angle);
			break;
		}
		if (DEBUG)
			draw_pixel(&cube->img, x, y, WHITE);
		cube->coord.temp_err = cube->coord.err;
		if (cube->coord.temp_err > -cube->coord.dx)
		{
			cube->coord.err -=cube->coord.dy;
			x += cube->coord.dir_x;
		}
		if (cube->coord.temp_err < cube->coord.dy)
		{
			cube->coord.err += cube->coord.dx;
			y += cube->coord.dir_y;
		}
	}
}

