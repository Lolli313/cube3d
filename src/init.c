/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:43:09 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/11 14:35:23 by aakerblo         ###   ########.fr       */
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
	cube->player_direction = 0;
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
	int	map_init[8][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 2, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
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
