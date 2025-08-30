/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:47:28 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/30 15:06:53 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	else if (keysym == XK_e)
		cube->keys.e_pressed = 1;
	else if (keysym == XK_Escape)
		cube->keys.esc_pressed = 1;
	else if (keysym == XK_Left)
		cube->keys.left_pressed = 1;
	else if (keysym == XK_Right)
		cube->keys.right_pressed = 1;
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
	else if (keysym == XK_e)
		cube->keys.e_pressed = 0;
	else if (keysym == XK_Escape)
		cube->keys.esc_pressed = 0;
	else if (keysym == XK_Left)
		cube->keys.left_pressed = 0;
	else if (keysym == XK_Right)
		cube->keys.right_pressed = 0;
	return (0);
}

int	mouse_handler(int x, int y, t_cube *cube)
{
	static int	prev_x = WIDTH / 2;
	int			dx;

	(void)y;
	dx = x - prev_x;
	if (dx != 0)
	{
		cube->p.player_direction += dx * MOUSE_SENSITIVITY;
		if (cube->p.player_direction < 0)
			cube->p.player_direction += 2 * PI;
		if (cube->p.player_direction > 0)
			cube->p.player_direction -= 2 * PI;
		cube->p.cam_x = cos(cube->p.player_direction);
		cube->p.cam_y = sin(cube->p.player_direction);
	}
	if (x != WIDTH / 2)
	{
#ifdef __linux__
		mlx_mouse_move(cube->mlx, cube->mlx_win, WIDTH / 2, HEIGHT / 2);
#elif __APPLE__
		mlx_mouse_move(cube->mlx_win, WIDTH / 2, HEIGHT / 2);
#endif
	}
	prev_x = WIDTH / 2;
	return (0);
}

void	update_player_direction(t_cube *cube, double delta_time)
{
	if (cube->keys.left_pressed)
	{
		cube->p.player_direction -= TURNSPEED * delta_time;
		if (cube->p.player_direction < 0)
			cube->p.player_direction += 2 * PI;
		cube->p.cam_x = cos(cube->p.player_direction);
		cube->p.cam_y = sin(cube->p.player_direction);
	}
	if (cube->keys.right_pressed)
	{
		cube->p.player_direction += TURNSPEED * delta_time;
		if (cube->p.player_direction >= 2 * PI)
			cube->p.player_direction -= 2 * PI;
		cube->p.cam_x = cos(cube->p.player_direction);
		cube->p.cam_y = sin(cube->p.player_direction);
	}
}

int	game_loop(t_cube *cube)
{
	double	delta_time;

	delta_time = get_delta_time();
	update_player_direction(cube, delta_time);
	if (cube->keys.esc_pressed)
		cleanup(cube);
	if (cube->keys.w_pressed)
		update_player_position(cube, UP);
	if (cube->keys.a_pressed)
		update_player_position(cube, LEFT);
	if (cube->keys.s_pressed)
		update_player_position(cube, DOWN);
	if (cube->keys.d_pressed)
		update_player_position(cube, RIGHT);
	handle_door(cube);
	render_image(cube);
	return (0);
}
