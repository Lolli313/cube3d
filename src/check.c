/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:59:26 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/11 16:10:32 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	check_wall_tile(t_cube *cube, int p_new_position_x, int p_new_position_y, int a)
{
	
	if (a == 1 && cube->map.map[cube->p_square_x - 1][cube->p_square_y] == 1 && 
		p_new_position_x < HEIGHT / MAP_X * (cube->p_square_x + 1))
			return (true);

	else if (a == 2 && cube->map.map[cube->p_square_x + 1][cube->p_square_y] == 1 && 
		p_new_position_x >= HEIGHT / MAP_X * (cube->p_square_x + 1))
			return (true);
	
	else if (a == 3 && cube->map.map[cube->p_square_x][cube->p_square_y - 1] == 1 && 
		p_new_position_y < HEIGHT / MAP_Y * (cube->p_square_y + 1))
			return (true);
			
	else if (a == 4 && cube->map.map[cube->p_square_x][cube->p_square_y + 1] == 1 && 
		p_new_position_y >= HEIGHT / MAP_Y * (cube->p_square_y + 1))
			return (true);
	return (false);
}
/*
bool	check_direction(t_cube *cube)
{
	
}*/
