/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:00 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/31 18:11:05 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
	cos(θ - π/2) = sin(θ)
	sin(θ - π/2) = -cos(θ)
	cos(θ + π/2) = -sin(θ)
	sin(θ + π/2) = cos(θ)
*/
/*
t_new_p*	check_direction(t_cube *cube, t_new_p *new_p, int dir)
{
	if (dir == 0)
	{
		new_p->p_new_position_x = (int)(cube->p_precise_x + (PLAYERSPEED * cube->p_cam_x));
		new_p->p_new_position_y = (int)(cube->p_precise_y + (PLAYERSPEED * cube->p_cam_y));
	}
	if (dir == 1)
	{
		new_p->p_new_position_x = (int)(cube->p_precise_x + (PLAYERSPEED * (-cube->p_cam_y)));
		new_p->p_new_position_y = (int)(cube->p_precise_y + (PLAYERSPEED * cube->p_cam_x));
	}
	if (dir == 2)
	{
		new_p->p_new_position_x = (int)(cube->p_precise_x + (PLAYERSPEED * (-cube->p_cam_x)));
		new_p->p_new_position_y = (int)(cube->p_precise_y + (PLAYERSPEED * (-cube->p_cam_y)));
	}
	if (dir == 3)
	{
		new_p->p_new_position_x = (int)(cube->p_precise_x + (PLAYERSPEED * cube->p_cam_y));
		new_p->p_new_position_y = (int)(cube->p_precise_y + (PLAYERSPEED * (-cube->p_cam_x)));
	}
	return (new_p);
}

t_new_p	check_new_position(t_cube *cube, t_new_p *new_p, int dir)
{
	new_p = check_direction(cube, new_p, dir);

	if (cube->map.map[cube->p_square_y][cube->p_square_x - 1] == 1 &&
		new_p->p_new_position_x < WIDTH / MAP_X * (cube->p_square_x))
			new_p->p_new_position_x = WIDTH / MAP_X * (cube->p_square_x);
	if (cube->map.map[cube->p_square_y][cube->p_square_x + 1] == 1 &&
		new_p->p_new_position_x + PLAYERSIZE > WIDTH / MAP_X * (cube->p_square_x + 1))
			new_p->p_new_position_x = WIDTH / MAP_X * (cube->p_square_x + 1);
	if (cube->map.map[cube->p_square_y - 1][cube->p_square_x] == 1 &&
		new_p->p_new_position_y < HEIGHT / MAP_Y * (cube->p_square_y))
			new_p->p_new_position_y = HEIGHT / MAP_Y * (cube->p_square_y);
	if (cube->map.map[cube->p_square_y + 1][cube->p_square_x] == 1 &&
		new_p->p_new_position_y + PLAYERSIZE > HEIGHT / MAP_Y * (cube->p_square_y + 1))
			new_p->p_new_position_y = HEIGHT / MAP_Y * (cube->p_square_y + 1);
	return (*new_p);
}*/

void	update_player_position(t_cube *cube, int dir)
{
	double delta_x, delta_y;
	int potential_x, potential_y;
	int tile_x, tile_y;
	
	if (dir == UP)
	{
		delta_x = PLAYERSPEED * cube->p_cam_x;
		delta_y = PLAYERSPEED * cube->p_cam_y;
	}
	else if (dir == DOWN)
	{
		delta_x = PLAYERSPEED * (-cube->p_cam_y);
		delta_y = PLAYERSPEED * cube->p_cam_x;
	}
	else if (dir == RIGHT)
	{
		delta_x = PLAYERSPEED * (-cube->p_cam_x);
		delta_y = PLAYERSPEED * (-cube->p_cam_y);
	}
	else
	{
		delta_x = PLAYERSPEED * cube->p_cam_y;
		delta_y = PLAYERSPEED * (-cube->p_cam_x);
	}
	
	cube->p_error_x += delta_x;
	cube->p_error_y += delta_y;
	
	int pixel_move_x = (int)cube->p_error_x;
	int pixel_move_y = (int)cube->p_error_y;
	
	if (pixel_move_x != 0)
	{
		cube->p_error_x -= pixel_move_x;
		cube->p_precise_x += delta_x;
		potential_x = (int)cube->p_precise_x;
		
		if (pixel_move_x > 0)
		{
			if (check_wall_tile(cube, potential_x, cube->p_position_y, RIGHT))
			{
				tile_x = (potential_x + PLAYERSIZE) / (WIDTH / MAP_X);
				cube->p_precise_x = tile_x * (WIDTH / MAP_X) - PLAYERSIZE;
			}
		}
		else
		{
			if (check_wall_tile(cube, potential_x, cube->p_position_y, LEFT))
			{
				tile_x = potential_x / (WIDTH / MAP_X);
				cube->p_precise_x = (tile_x + 1) * (WIDTH / MAP_X);
			}
		}
		cube->p_position_x = (int)cube->p_precise_x;
	}
	
	if (pixel_move_y != 0)
	{
		cube->p_error_y -= pixel_move_y;
		cube->p_precise_y += delta_y;
		potential_y = (int)cube->p_precise_y;
		
		if (pixel_move_y > 0)
		{
			if (check_wall_tile(cube, cube->p_position_x, potential_y, DOWN))
			{
				tile_y = (potential_y + PLAYERSIZE) / (HEIGHT / MAP_Y);
				cube->p_precise_y = tile_y * (HEIGHT / MAP_Y) - PLAYERSIZE;
			}
		}
		else
		{
			if (check_wall_tile(cube, cube->p_position_x, potential_y, UP))
			{
				tile_y = potential_y / (HEIGHT / MAP_Y);
				cube->p_precise_y = (tile_y + 1) * (HEIGHT / MAP_Y);
			}
		}
		cube->p_position_y = (int)cube->p_precise_y;
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