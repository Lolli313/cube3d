/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:00 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/10 13:49:10 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_player_position(t_cube *cube, int p_new_position_x, int p_new_position_y)
{
	int temp1;
	int temp2;
	int	temp3;
	int	temp4;

	temp1 = cube->p_position_x / (HEIGHT / MAP_X);
	printf("temp1 = %d\n", temp1);
	temp2 = p_new_position_x / (HEIGHT / MAP_X);
	printf("temp2 = %d\n", temp2);
	temp3 = cube->p_position_y / (HEIGHT / MAP_Y);
	printf("temp3 = %d\n", temp1);
	temp4 = p_new_position_y / (HEIGHT / MAP_Y);
	printf("temp4 = %d\n", temp2);

	if (p_new_position_x <= HEIGHT / MAP_X || temp1 < cube->p_square_x)
	{
		if (p_new_position_x < HEIGHT / MAP_X || (cube->p_square_x <= 1 && temp2 < cube->p_square_x))
			return ;
		else
			cube->p_square_x--;
	}
	else if (p_new_position_x >= HEIGHT - (HEIGHT / MAP_X) || temp2 > cube->p_square_x)
	{
		if (p_new_position_x >= HEIGHT - HEIGHT / MAP_X || (cube->p_square_x >= MAP_X && temp2 > cube->p_square_x))
			return ;
		else
			cube->p_square_x++;
	}
	else if (p_new_position_y <= WIDTH / MAP_Y || temp3 < cube->p_square_y)
	{
		if (p_new_position_y < WIDTH / MAP_Y || (cube->p_square_y <= 1 && temp4 < cube->p_square_y))
			return ;
		else
			cube->p_square_y--;
	}
	else if (p_new_position_y >= WIDTH - (WIDTH / MAP_Y) || temp3 > cube->p_square_y)
	{
		if (p_new_position_y >= WIDTH - WIDTH / MAP_Y || (cube->p_square_y >= MAP_Y && temp4 > cube->p_square_y))
			return ;
		else
			cube->p_square_y++;
	}
	cube->p_position_x = p_new_position_x;
	cube->p_position_y = p_new_position_y;
}

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
			draw_pixel(&cube->img, y, x, cube->color);
			cube->color = DARK_BLUE;
		}
	}
	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->img.img_addr, 0, 0);
}

void	init_cube(t_cube *cube)
{
	cube->mlx = mlx_init();
	cube->mlx_win = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "Test");
	int	map_init[8][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 2, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
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
				cube->p_position_x = WIDTH / 8 * i;
				cube->p_position_y = HEIGHT / 8 * j;
				cube->p_square_x = i;
				cube->p_square_y = j;
			}
		}				
}

int	main(int ac, char **av)
{
	t_cube cube;

	(void)ac;
	(void)av;
	init_cube(&cube);
	init_keys(&cube);
	init_hooks(&cube);
	init_image(&cube);
	render_image(&cube);
	mlx_loop(cube.mlx);
}