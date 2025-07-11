/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:00 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/11 14:59:48 by aakerblo         ###   ########.fr       */
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

	if (p_new_position_x < cube->p_position_x)
	{
		if (check_wall_tile(cube, p_new_position_x, p_new_position_y, 1) && temp2 < cube->p_square_x)
			return ;
		else if (temp2 < cube->p_square_x)
			cube->p_square_x--;
	}
	else if (p_new_position_x > cube->p_position_x)
	{
		if (check_wall_tile(cube, p_new_position_x, p_new_position_y, 2) && temp2 > cube->p_square_x)
			return ;
		else if (temp2 > cube->p_square_x)
			cube->p_square_x++;
	}
	else if (p_new_position_y < cube->p_position_y)
	{
		if (check_wall_tile(cube, p_new_position_x, p_new_position_y, 3) && temp4 < cube->p_square_y)
			return ;
		else if (temp4 < cube->p_square_y)
			cube->p_square_y--;
	}
	else if (p_new_position_y > cube->p_position_y)
	{
		if (check_wall_tile(cube, p_new_position_x, p_new_position_y, 4) && temp4 > cube->p_square_y)
			return ;
		else if (temp4 > cube->p_square_y)
			cube->p_square_y++;
	}
	cube->p_position_x = p_new_position_x;
	cube->p_position_y = p_new_position_y;
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