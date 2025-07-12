/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:36:27 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/12 11:58:38 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH)
	{
		dst = img->pixel_addr + (y * img->line_length + x
				*(img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

double	scale(double value, double origin_max,
			double target_min, double target_max)
{
	double	origin_min;

	origin_min = 0;
	return ((value - origin_min) * (target_max - target_min)
		/ (origin_max - origin_min) + target_min);
}

void	bresenham(t_cube *cube, int start_x, int start_y, int end_x, int end_y)
{
	int m;
	int	slope_error;
	int	temp_x;
	int temp_y;

	m = 2 * (end_y - start_y);
	slope_error = m - (end_x - start_x);
	temp_x = start_x;
	temp_y = start_y;
	while (temp_x <= end_x)
	{
		draw_pixel(&cube->img, temp_y, temp_x, WHITE);
		slope_error += m;
		if (slope_error >= 0)
		{
			temp_y++;
			slope_error -= 2 * (end_x - start_x);
		}
		temp_x++;
	}
}

void	draw_line(t_cube *cube)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = cube->p_position_x + (PLAYERSIZE / 2);
	start_y = cube->p_position_y + (PLAYERSIZE / 2);
	end_x = start_x + (PLAYERDIRECTIONSIZE * cos(cube->player_direction));
	end_y = start_y + (PLAYERDIRECTIONSIZE * sin(cube->player_direction));
	bresenham(cube, start_x, start_y, end_x, end_y);	
	bresenham(cube, start_x, start_y - 1, end_x, end_y - 1);	
	bresenham(cube, start_x, start_y + 1, end_x, end_y + 1);	
}

// to find x-coordinate use x = PLAYERDIRECTIONSIZE * cos(angle)
// to find y-coordinate use y = PLAYERDIRECTIONSIZE * sin(angle)

void	render_image(t_cube *cube)
{
	int	x;
	int	y;
	int	a;
	int	b;

	mlx_destroy_image(cube->mlx, cube->img.img_addr);
	init_image(cube);
	x = -1;
	a = -1;
	while (++x < WIDTH)
	{
		if (x % (WIDTH / MAP_X) == 0)
			a++;
		y = -1;
		b = -1;
		while (++y < HEIGHT)
		{
			if (y % (HEIGHT / MAP_Y) == 0)
				b++;
			if (cube->map.map[a][b] == 1)
				cube->color = DARK_RED;
			else if (cube->map.map[a][b] == 0)
				cube->color = DARK_BLUE;
			if ((x >= cube->p_position_x && x <= cube->p_position_x + PLAYERSIZE) && (y >= cube->p_position_y && y <= cube->p_position_y + PLAYERSIZE))
				cube->color = GREEN;
			if (x == PLAYERDIRECTIONSIZE * cos(cube->player_direction) && y == PLAYERDIRECTIONSIZE * sin(cube->player_direction))
				cube->color = WHITE;
			draw_pixel(&cube->img, y, x, cube->color);
			cube->color = DARK_BLUE;
		}
	}
	draw_line(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->img.img_addr, 0, 0);
}
