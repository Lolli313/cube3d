/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:17:39 by njung             #+#    #+#             */
/*   Updated: 2025/09/11 14:47:27 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_texture_element(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'F'
		|| c == 'C');
}

int	is_player_rotation(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_map_element(char c)
{
	return (c == '1' || c == '0' || c == ' ');
}

void	set_player_position(t_cube *cube, char direction, int row, int col)
{
	cube->map.map[row][col] = 2;
	if (direction == 'N')
		cube->p.player_direction = 3 * PI / 2;
	else if (direction == 'S')
		cube->p.player_direction = PI / 2;
	else if (direction == 'E')
		cube->p.player_direction = 0;
	else if (direction == 'W')
		cube->p.player_direction = PI;
	cube->p.cam_x = cos(cube->p.player_direction);
	cube->p.cam_y = sin(cube->p.player_direction);
	cube->p.position_x = (TILESIZE * col + TILESIZE / 2) + (PLAYERSIZE / 2);
	cube->p.position_y = (TILESIZE * row) + (PLAYERSIZE / 2);
	cube->p.precise_x = (double)cube->p.position_x;
	cube->p.precise_y = (double)cube->p.position_y;
	cube->p.error_x = 0.0;
	cube->p.error_y = 0.0;
	cube->p.square_x = row;
	cube->p.square_y = row;
}

void	init_counters(t_count *counter)
{
	counter->no_count = 0;
	counter->so_count = 0;
	counter->we_count = 0;
	counter->ea_count = 0;
	counter->f_count = 0;
	counter->c_count = 0;
}
