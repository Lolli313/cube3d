/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:36:27 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/31 11:08:18 by aakerblo         ###   ########.fr       */
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

void	render_image(t_cube *cube)
{
	int	x;
	int	y;
	int	a;
	int	b;

	mlx_destroy_image(cube->mlx, cube->img.img_addr);
	init_image(cube);
	y = -1;
	a = -1;
	while (++y < WIDTH)
	{
		if (y % (WIDTH / MAP_X) == 0)
			a++;
		x = -1;
		b = -1;
		while (++x < HEIGHT)
		{
			if (x % (HEIGHT / MAP_Y) == 0)
				b++;
			if (cube->map.map[a][b] == 1)
				cube->color = DARK_RED;
			else if (cube->map.map[a][b] == 0)
				cube->color = DARK_BLUE;
			if ((y >= cube->p_position_y && y <= cube->p_position_y + PLAYERSIZE) && (x >= cube->p_position_x && x <= cube->p_position_x + PLAYERSIZE))
				cube->color = GREEN;
			draw_pixel(&cube->img, x, y, cube->color);
			cube->color = DARK_BLUE;
		}
	}
	draw_rays(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->img.img_addr, 0, 0);
}
