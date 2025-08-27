/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:43:09 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/27 17:38:38 by aakerblo         ###   ########.fr       */
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
	cube->keys.e_pressed = 0;
	cube->keys.esc_pressed = 0;
	cube->keys.left_pressed = 0;
	cube->keys.right_pressed = 0;
	cube->p.player_direction = 0;
	cube->p.cam_x = cos(cube->p.player_direction);
	cube->p.cam_y = sin(cube->p.player_direction);
}

void	init_hooks(t_cube *cube)
{
	mlx_hook(cube->mlx_win, KEY_PRESS, 1L << 0, key_press_handler, cube);
	mlx_hook(cube->mlx_win, KEY_RELEASE, 1L << 1, key_release_handler, cube);
	mlx_hook(cube->mlx_win, MOTION_NOTIFY, 1L << 6, mouse_handler, cube);
#ifdef __linux__
	mlx_mouse_hide(cube->mlx, cube->mlx_win);
	mlx_mouse_move(cube->mlx, cube->mlx_win, WIDTH / 2, HEIGHT / 2);
#elif __APPLE__
	mlx_mouse_hide();
	mlx_mouse_move(cube->mlx_win, WIDTH / 2, HEIGHT / 2);
#endif
	mlx_loop_hook(cube->mlx, game_loop, cube);
	mlx_hook(cube->mlx_win, DESTROY_WINDOW, 0L, cleanup, cube);
}

void	init_map(t_cube *cube)
{
	int	i;
	int	j;

	cube->nbr_doors = 0;
	i = -1;
	while (++i < MAP_Y)
	{
		j = -1;
		while (++j < MAP_X)
			cube->map.map[i][j] = 0;
	}
}

void	init_cube(t_cube *cube)
{
	cube->mlx = mlx_init();
	cube->mlx_win = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "Test");
	init_map(cube);
}
