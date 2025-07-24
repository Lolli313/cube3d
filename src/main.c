/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:00 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/24 16:52:32 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
	cos(θ - π/2) = sin(θ)
	sin(θ - π/2) = -cos(θ)
	cos(θ + π/2) = -sin(θ)
	sin(θ + π/2) = cos(θ)
*/

t_new_p	check_new_position(t_cube *cube, t_new_p *new_p, int keysym)
{
	if (keysym == XK_w)
	{
		new_p->p_new_position_x = cube->p_position_x + (PLAYERSPEED * cos(cube->player_direction));
		new_p->p_new_position_y = cube->p_position_y + (PLAYERSPEED * sin(cube->player_direction));
	}
	else if (keysym == XK_s)
	{
		new_p->p_new_position_x = cube->p_position_x - (PLAYERSPEED * cos(cube->player_direction));
		new_p->p_new_position_y = cube->p_position_y - (PLAYERSPEED * sin(cube->player_direction));
	}
	else if (keysym == XK_a)
	{
		new_p->p_new_position_x = cube->p_position_x + (PLAYERSPEED * cos(cube->player_direction - (PI / 2)));
		new_p->p_new_position_y = cube->p_position_y + (PLAYERSPEED * sin(cube->player_direction - (PI / 2)));
	}
	else if (keysym == XK_d)
	{
		new_p->p_new_position_x = cube->p_position_x + (PLAYERSPEED * cos(cube->player_direction + (PI / 2)));
		new_p->p_new_position_y = cube->p_position_y + (PLAYERSPEED * sin(cube->player_direction + (PI / 2)));
	}
	return (*new_p);
}

void	update_player_position(t_cube *cube, int keysym)
{
	int temp1;
	int	temp2;
	t_new_p new_p;

	new_p = check_new_position(cube, &new_p, keysym);
	temp1 = new_p.p_new_position_x / (WIDTH / MAP_X);
	temp2 = new_p.p_new_position_y / (HEIGHT / MAP_Y);
	if (new_p.p_new_position_x < cube->p_position_x)
	{
		if (check_wall_tile(cube, new_p.p_new_position_x, new_p.p_new_position_y, 1) && temp1 < cube->p_square_x)
			return ;
		else if (temp1 < cube->p_square_x)
			cube->p_square_x--;
	}
	if (new_p.p_new_position_x > cube->p_position_x)
	{
		if (check_wall_tile(cube, new_p.p_new_position_x, new_p.p_new_position_y, 2) && temp1 > cube->p_square_x)
			return ;
		else if (temp1 > cube->p_square_x)
			cube->p_square_x++;
	}
	if (new_p.p_new_position_y < cube->p_position_y)
	{
		if (check_wall_tile(cube, new_p.p_new_position_x, new_p.p_new_position_y, 3) && temp2 < cube->p_square_y)
			return ;
		else if (temp2 < cube->p_square_y)
			cube->p_square_y--;
	}
	if (new_p.p_new_position_y > cube->p_position_y)
	{
		if (check_wall_tile(cube, new_p.p_new_position_x, new_p.p_new_position_y, 4) && temp2 > cube->p_square_y)
			return ;
		else if (temp2 > cube->p_square_y)
			cube->p_square_y++;
	}
	cube->p_position_x = new_p.p_new_position_x;
	cube->p_position_y = new_p.p_new_position_y;
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