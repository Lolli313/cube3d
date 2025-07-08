/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:00 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/07 17:16:34 by aakerblo         ###   ########.fr       */
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

int	key_handler(int keysym, t_cube *cube)
{
	if (keysym == XK_w)
		(void);
	if (keysym == XK_a)
		(void);
	if (keysym == XK_s)
		(void);
	if (keysym == XK_d)
		(void);
	
}

void	init_hooks(t_cube *cube)
{
	mlx_key_hook(cube->mlx_win, key_handler, cube);
	mlx_mouse_hook(cube->mlx_win, mouse_handler, cube);
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

void	render_point(t_cube *cube, int x, int y)
{
	draw_pixel(&cube->img, x, y, 0x00FFFF);
}

void	render_image(t_cube *cube)
{
	int	x;
	int	y;

	mlx_destroy_image(cube->mlx, cube->img.img_addr);
	init_image(cube);
	x = -1;
	while (++x < 800)
	{
		y = -1;
		while (++y < 800)
		{
			
		}
	}
}

int	main(int ac, char **av)
{
	t_cube cube;
	int map[8][8] = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 'P', 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}
	};

	(void)ac;
	(void)av;
	cube.mlx = mlx_init();
	cube.mlx_win = mlx_new_window(cube.mlx, 800, 800, "Test");
	init_hooks(&cube);
	init_image(&cube);
	mlx_loop(cube.mlx);
}