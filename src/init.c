/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:43:09 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/10 14:03:57 by aakerblo         ###   ########.fr       */
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
}

void	init_hooks(t_cube *cube)
{
	mlx_hook(cube->mlx_win, KEY_PRESS, 1L<<0, key_press_handler, cube);
	mlx_hook(cube->mlx_win, KEY_RELEASE, 1L<<1, key_release_handler, cube);
	mlx_loop_hook(cube->mlx, game_loop, cube);
	mlx_hook(cube->mlx_win, DESTROY_WINDOW, 0L, cleanup, cube);
}
