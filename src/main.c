/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:00 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/08 13:37:29 by aakerblo         ###   ########.fr       */
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

void	update_player_position(t_cube *cube, int p_new_position_x, int p_new_position_y)
{
	cube->map.map[p_new_position_x][p_new_position_y] = 2;
	cube->map.map[cube->p_position_x][cube->p_position_y] = 0;
	cube->p_position_x = p_new_position_x;
	cube->p_position_y = p_new_position_y;
}

int	key_handler(int keysym, t_cube *cube)
{
	if (keysym == XK_w)
	{
		if (cube->map.map[cube->p_position_x - 1][cube->p_position_y] != 1)
			update_player_position(cube, cube->p_position_x - 1, cube->p_position_y);
	}
	if (keysym == XK_a)
	{
		if (cube->map.map[cube->p_position_x][cube->p_position_y - 1] != 1)
			update_player_position(cube, cube->p_position_x, cube->p_position_y - 1);
	}
	if (keysym == XK_s)
	{
		if (cube->map.map[cube->p_position_x + 1][cube->p_position_y] != 1)
			update_player_position(cube, cube->p_position_x + 1, cube->p_position_y);
	}
	if (keysym == XK_d)
	{
		if (cube->map.map[cube->p_position_x][cube->p_position_y + 1] != 1)
			update_player_position(cube, cube->p_position_x, cube->p_position_y + 1);
	}
	if (keysym == XK_Escape)
		cleanup(cube);
	render_image(cube);
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

void	init_cube(t_cube *cube)
{
	cube->mlx = mlx_init();
	cube->mlx_win = mlx_new_window(cube->mlx, 800, 800, "Test");
	int	map_init[8][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 2, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
	};
	
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			cube->map.map[i][j] = map_init[i][j];
			if (map_init[i][j] == 2)
			{
				cube->p_position_x = i;
				cube->p_position_y = j;
			}
		}				
}

int	main(int ac, char **av)
{
	t_cube cube;

	(void)ac;
	(void)av;
	init_cube(&cube);
	init_hooks(&cube);
	init_image(&cube);
	render_image(&cube);
	mlx_loop(cube.mlx);
}