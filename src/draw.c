/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:36:27 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/28 17:03:11 by aakerblo         ###   ########.fr       */
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

	mlx_destroy_image(cube->mlx, cube->img.img_addr);
	init_image(cube);
	y = -1;
	while (++y < WIDTH / 2)
	{
		x = -1;
		while (++x < HEIGHT)
			draw_pixel(&cube->img, x, y, cube->map.ceiling);
	}
	while (++y < WIDTH)
	{
		x = -1;
		while (++x < HEIGHT)
			draw_pixel(&cube->img, x, y, cube->map.floor);
	}
	raycasting(cube);
	draw_minimap(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->img.img_addr, 0, 0);
}
