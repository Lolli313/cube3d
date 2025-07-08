/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:00 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/08 11:38:57 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_image(t_cube *cube)
{
	cube->img.img_addr = mlx_new_image(cube->mlx, 800, 800);
	cube->img.pixel_addr = mlx_get_data_addr(cube->img.img_addr,
			&cube->img.bits_per_pixel, &cube->img.line_length,
			&cube->img.endian);
}

int	cleanup(t_cube *cube)
{
	mlx_destroy_window(cube->mlx, cube->mlx_win);
	mlx_destroy_image(cube->mlx, cube->img.img_addr);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit(0);
}

int	key_handler(int keysym, t_cube *cube)
{
	if (keysym == XK_w)
		(void)keysym;
	if (keysym == XK_a)
		(void)keysym;
	if (keysym == XK_s)
		(void)keysym;
	if (keysym == XK_d)
		(void)keysym;
	if (keysym == XK_Escape)
		cleanup(cube);
	return (0);
}

void	init_hooks(t_cube *cube)
{
	mlx_key_hook(cube->mlx_win, key_handler, cube);
//	mlx_mouse_hook(cube->mlx_win, mouse_handler, cube);
	mlx_hook(cube->mlx_win, 17, 0, cleanup, cube);
}

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 800 && y >= 0 && y < 800)
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

void	render_point(t_cube *cube, int x, int y)
{
	draw_pixel(&cube->img, x, y, 0x00FFFF);
}

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
	while (++x < 800)
	{
		if (x % 100 == 0)
			a++;
		y = -1;
		b = -1;
		while (++y < 800)
		{
			if (y % 100 == 0)
				b++;
			if (cube->map.map[a][b] == 1)
				cube->color = DARK_RED;
			else if (cube->map.map[a][b] == 0)
				cube->color = DARK_BLUE;
			else if (cube->map.map[a][b] == 2)
				cube->color = GREEN;
			draw_pixel(&cube->img, y, x, cube->color);
		}
	}
	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->img.img_addr, 0, 0);
}

int	main(int ac, char **av)
{
	t_cube cube;
	
	int	map_init[8][8] = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}
	};
	
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			cube.map.map[i][j] = map_init[i][j];

	(void)ac;
	(void)av;
	cube.mlx = mlx_init();
	cube.mlx_win = mlx_new_window(cube.mlx, 800, 800, "Test");
	init_hooks(&cube);
	init_image(&cube);
	render_image(&cube);
	mlx_loop(cube.mlx);
}