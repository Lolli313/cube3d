/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:43:09 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/09 15:14:53 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_visited_map(int **visited, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			visited[y][x] = 0;
			x++;
		}
		y++;
	}
}

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

void	init_cube(t_cube *cube)
{
	cube->mlx = mlx_init();
	cube->mlx_win = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "Test");
	cube->door = NULL;
	cube->map.door = NULL;
	cube->map.nbr_doors = 0;
	cube->paint = NULL;
	cube->map.nbr_paintings = 0;
}
