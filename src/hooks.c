/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:47:28 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/12 17:50:04 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	cleanup(t_cube *cube)
{
	mlx_destroy_window(cube->mlx, cube->mlx_win);
	mlx_destroy_image(cube->mlx, cube->img.img_addr);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit(0);
}

int	key_press_handler(int keysym, t_cube *cube)
{
	if (keysym == XK_w)
		cube->keys.w_pressed = 1;
	else if (keysym == XK_a)
		cube->keys.a_pressed = 1;
	else if (keysym == XK_s)
		cube->keys.s_pressed = 1;
	else if (keysym == XK_d)
		cube->keys.d_pressed = 1;
	else if (keysym == XK_Escape)
		cube->keys.esc_pressed = 1;
	return (0);
}

int	key_release_handler(int keysym, t_cube *cube)
{
	if (keysym == XK_w)
		cube->keys.w_pressed = 0;
	else if (keysym == XK_a)
		cube->keys.a_pressed = 0;
	else if (keysym == XK_s)
		cube->keys.s_pressed = 0;
	else if (keysym == XK_d)
		cube->keys.d_pressed = 0;
	else if (keysym == XK_Escape)
		cube->keys.esc_pressed = 0;
	return (0);
}

int	game_loop(t_cube *cube)
{
	if (cube->keys.esc_pressed)
		cleanup(cube);
	if (cube->keys.w_pressed)
		update_player_position(cube, cube->p_position_x, cube->p_position_y - PLAYERSPEED);
	if (cube->keys.a_pressed)
		update_player_position(cube, cube->p_position_x - PLAYERSPEED, cube->p_position_y);
	if (cube->keys.s_pressed)
		update_player_position(cube, cube->p_position_x, cube->p_position_y + PLAYERSPEED);
	if (cube->keys.d_pressed)
		update_player_position(cube, cube->p_position_x + PLAYERSPEED, cube->p_position_y);
	if (cube->keys.w_pressed || cube->keys.a_pressed || cube->keys.s_pressed || cube->keys.d_pressed)
	{
		printf("p_square_x is %d and p_square_y is %d\n", cube->p_square_x, cube->p_square_y);
		printf("position_x = %d and position_y is %d\n", cube->p_position_x, cube->p_position_y);
		render_image(cube);
	}
	return (0);
}
