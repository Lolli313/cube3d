/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:43:09 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/01 14:42:37 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_image(t_cube *cube)
{
	cube->img.img_addr = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	cube->img.pixel_addr = mlx_get_data_addr(cube->img.img_addr,
			&cube->img.bits_per_pixel, &cube->img.line_length,
			&cube->img.endian);
}

void	init_keys(t_cube *cube)
{
	cube->keys.w_pressed = 0;
	cube->keys.a_pressed = 0;
	cube->keys.s_pressed = 0;
	cube->keys.d_pressed = 0;
	cube->keys.esc_pressed = 0;
	cube->keys.left_pressed = 0;
	cube->keys.right_pressed = 0;
	cube->p.player_direction = PI / 2;
	cube->p.cam_x = cos(cube->p.player_direction);
	cube->p.cam_y = sin(cube->p.player_direction);
}

void	init_hooks(t_cube *cube)
{
	mlx_hook(cube->mlx_win, KEY_PRESS, 1L<<0, key_press_handler, cube);
	mlx_hook(cube->mlx_win, KEY_RELEASE, 1L<<1, key_release_handler, cube);
	mlx_loop_hook(cube->mlx, game_loop, cube);
	mlx_hook(cube->mlx_win, DESTROY_WINDOW, 0L, cleanup, cube);
}

void	init_cube(t_cube *cube)
{
	cube->mlx = mlx_init();
	cube->mlx_win = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "Test");
	int	map_init[MAP_X][MAP_Y] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 2, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
	};
	
	for (int i = 0; i < MAP_X; i++)
		for (int j = 0; j < MAP_Y; j++)
		{
			cube->map.map[i][j] = map_init[i][j];
			if (map_init[i][j] == 2)
			{
				cube->p.position_x = WIDTH / MAP_X * i;
				cube->p.position_y = HEIGHT / MAP_Y * j;
				cube->p.precise_x = (double)cube->p.position_x;
				cube->p.precise_y = (double)cube->p.position_y;
				cube->p.error_x = 0.0;
				cube->p.error_y = 0.0;
				cube->p.square_x = i;
				cube->p.square_y = j;
			}
		}				
}
