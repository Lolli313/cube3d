/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:34:58 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/24 12:15:44 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// to find x-coordinate use x = PLAYERDIRECTIONSIZE * cos(angle)
// to find y-coordinate use y = PLAYERDIRECTIONSIZE * sin(angle)
/*
void	switch_endpoints(t_cube *cube)
{
	int temp;

	temp = cube->coord.start_x;
	cube->coord.start_x = cube->coord.end_x;
	cube->coord.end_x = temp;
	temp = cube->coord.start_y;
	cube->coord.start_y = cube->coord.end_y;
	cube->coord.end_y = temp;
}

void	switch_x_and_y(t_cube *cube)
{
	int temp;

	temp = cube->coord.start_x;
	cube->coord.start_x = cube->coord.start_y;
	cube->coord.start_y = temp;
	temp = cube->coord.end_x;
	cube->coord.end_x = cube->coord.end_y;
	cube->coord.end_y = temp;
}

void	prepare_coords(t_cube *cube)
{
	cube->coord.start_x = cube->p_position_x + (PLAYERSIZE / 2);
	cube->coord.start_y = cube->p_position_y + (PLAYERSIZE / 2);
	cube->coord.end_x = cube->coord.start_x + (PLAYERDIRECTIONSIZE * cos(cube->player_direction));
	cube->coord.end_y = cube->coord.start_y + (PLAYERDIRECTIONSIZE * sin(cube->player_direction));
	cube->coord.dx = cube->coord.end_x - cube->coord.start_x;
	cube->coord.dy = cube->coord.end_y - cube->coord.start_y;
	if (cube->coord.dx < 0)
	{
		cube->coord.is_dx_positive = false;
		cube->coord.dx = abs(cube->coord.dx);
		switch_endpoints(cube);
	}
	else
		cube->coord.is_dx_positive = true;
	if (cube->coord.dy < 0)
	{
		cube->coord.is_dy_positive = false;
		cube->coord.dy = abs(cube->coord.dy);
	}
	else
		cube->coord.is_dy_positive = true;
	if (cube->coord.dy > cube->coord.dx)
	{
		cube->coord.is_line_steep = true;
		switch_x_and_y(cube);
		cube->coord.dx = cube->coord.end_x - cube->coord.start_x;
		cube->coord.dy = cube->coord.end_y - cube->coord.start_y;
		
		bool temp_is_dy_positive = cube->coord.is_dy_positive;
		cube->coord.is_dy_positive = cube->coord.is_dx_positive;
		cube->coord.is_dx_positive = temp_is_dy_positive;
		
		cube->coord.dx = abs(cube->coord.dx);
		cube->coord.dy = abs(cube->coord.dy);
		
		if (cube->coord.dx < 0)
		{
			cube->coord.dx = -cube->coord.dx;
			cube->coord.is_dx_positive = !cube->coord.is_dx_positive;
			switch_endpoints(cube);
			cube->coord.dy = cube->coord.end_y - cube->coord.start_y;
		}
	}
	else
		cube->coord.is_line_steep = false;
}

void	draw_pixel_with_transform(t_cube *cube, int x, int y, int color)
{
	if (cube->coord.is_line_steep == true)
	{
		draw_pixel(&cube->img, y, x, color);
	}
	else
	{
		draw_pixel(&cube->img, x, y, color);
	}
}

void	bresenham(t_cube *cube)
{
	int delta_y_doubled;
	int	delta_x_doubled;
	int	slope_error;
	int	temp_x;
	int temp_y;

	delta_y_doubled = 2 * cube->coord.dy;
	delta_x_doubled = 2 * cube->coord.dx;
	slope_error = delta_y_doubled - cube->coord.dx;
	
	temp_x = cube->coord.start_x;
	temp_y = cube->coord.start_y;
	draw_pixel_with_transform(cube, temp_x, temp_y, WHITE);
	
	while (temp_x < cube->coord.end_x)
	{
		temp_x++;
		slope_error += delta_y_doubled;
		if (slope_error >= 0)
		{
			if (cube->coord.is_dy_positive == true)
				temp_y++;
			else
				temp_y--;
			slope_error -= delta_x_doubled;
		}
		draw_pixel_with_transform(cube, temp_x, temp_y, WHITE);
	}
}*/

void	prepare_coords(t_cube *cube)
{
	cube->coord.start_x = cube->p_position_x + (PLAYERSIZE / 2);
	cube->coord.start_y = cube->p_position_y + (PLAYERSIZE / 2);
	cube->coord.end_x = cube->coord.start_x + (PLAYERDIRECTIONSIZE * cos(cube->player_direction));
	cube->coord.end_y = cube->coord.start_y + (PLAYERDIRECTIONSIZE * sin(cube->player_direction));
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

void	draw_line(t_cube *cube)
{
	int x;
	int y;
	
	prepare_coords(cube);
	draw_pixel(&cube->img, cube->coord.start_x, cube->coord.start_y, RED);
	x = cube->coord.start_x;
	y = cube->coord.start_y;
	while (1)
	{
		if (x != cube->coord.start_x || y != cube->coord.start_y)
			draw_pixel(&cube->img, x, y, WHITE);
		if (x == cube->coord.end_x && y == cube->coord.end_y)
			break;
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
