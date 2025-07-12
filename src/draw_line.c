/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:34:58 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/12 18:42:58 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// to find x-coordinate use x = PLAYERDIRECTIONSIZE * cos(angle)
// to find y-coordinate use y = PLAYERDIRECTIONSIZE * sin(angle)

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
		// After swapping x and y, we need to recalculate dx and dy and their signs
		cube->coord.dx = cube->coord.end_x - cube->coord.start_x;
		cube->coord.dy = cube->coord.end_y - cube->coord.start_y;
		
		// We also need to handle signs again after swapping
		bool temp_is_dy_positive = cube->coord.is_dy_positive;
		cube->coord.is_dy_positive = cube->coord.is_dx_positive;
		cube->coord.is_dx_positive = temp_is_dy_positive;
		
		// Reset dx and dy to absolute values for the algorithm
		cube->coord.dx = abs(cube->coord.dx);
		cube->coord.dy = abs(cube->coord.dy);
		
		// Ensure dx is positive (needed for the algorithm)
		if (cube->coord.dx < 0)
		{
			cube->coord.dx = -cube->coord.dx;
			cube->coord.is_dx_positive = !cube->coord.is_dx_positive;
			switch_endpoints(cube);
			// Recalculate dy after swapping endpoints
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
		// For steep lines, swap x and y when drawing
		draw_pixel(&cube->img, y, x, color);
	}
	else
	{
		// For non-steep lines, draw normally
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

	// Use the absolute values since we've already handled signs
	delta_y_doubled = 2 * cube->coord.dy;
	delta_x_doubled = 2 * cube->coord.dx;
	slope_error = delta_y_doubled - cube->coord.dx;
	
	// Ensure we're starting at the exact starting point
	temp_x = cube->coord.start_x;
	temp_y = cube->coord.start_y;
	// Draw the first pixel at the exact starting point
	draw_pixel_with_transform(cube, temp_x, temp_y, WHITE);
	
	while (temp_x < cube->coord.end_x) // Use < instead of <= to avoid potential overlap
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
}

void	draw_line(t_cube *cube)
{
	// Calculate the true center of the player - this is our actual starting point
	int player_center_x = cube->p_position_x + (PLAYERSIZE / 2);
	int player_center_y = cube->p_position_y + (PLAYERSIZE / 2);
	
	// We'll skip the coordinate transformations and draw line directly
	int end_x = player_center_x + (PLAYERDIRECTIONSIZE * cos(cube->player_direction));
	int end_y = player_center_y + (PLAYERDIRECTIONSIZE * sin(cube->player_direction));
	
	// Always draw the starting point at player center
	draw_pixel(&cube->img, player_center_x, player_center_y, RED);
	
	// Then draw a direct line - this simpler approach might fix the alignment issues
	int dx = abs(end_x - player_center_x);
	int dy = abs(end_y - player_center_y);
	int sx = player_center_x < end_x ? 1 : -1;
	int sy = player_center_y < end_y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;
	
	int x = player_center_x;
	int y = player_center_y;
	
	while (1)
	{
		if (x != player_center_x || y != player_center_y) // Don't draw starting point twice
			draw_pixel(&cube->img, x, y, WHITE);
		
		if (x == end_x && y == end_y)
			break;
			
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y += sy;
		}
	}
}
