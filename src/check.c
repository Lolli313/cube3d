/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:59:26 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/29 15:48:28 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	check_up_wall(t_cube *cube, int new_y)
{
	int	tile_x_right;
	int	tile_y;
	int	tile_x_left;

	tile_x_right = (cube->p.position_x + PLAYERSIZE / 2) / TILESIZE;
	tile_x_left = (cube->p.position_x - PLAYERSIZE / 2) / TILESIZE;
	tile_y = (new_y - PLAYERSIZE / 2) / TILESIZE;
//	printf("tile x right: %d, tile x left: %d, current y: %d, new_y: %d, tile y: %d\n", tile_x_right, tile_x_left, cube->p.position_y, new_y + (PLAYERSIZE / 2), tile_y);
	if (tile_x_right < 0 || tile_x_right >= cube->map.width || tile_x_left < 0 || tile_x_left >= cube->map.width
		|| tile_y < 0 || tile_y >= cube->map.height)
		return (true);
	return (cube->map.map[tile_y][tile_x_right] == 1
			|| cube->map.map[tile_y][tile_x_left] == 1
			|| cube->map.map[tile_y][tile_x_right] == 3
			|| cube->map.map[tile_y][tile_x_left] == 3);
}

bool	check_down_wall(t_cube *cube, int new_y)
{
	int	tile_x_right;
	int	tile_y;
	int	tile_x_left;

	tile_x_right = (cube->p.position_x + PLAYERSIZE / 2) / TILESIZE;
	tile_x_left = (cube->p.position_x - PLAYERSIZE / 2) / TILESIZE;
	tile_y = (new_y + PLAYERSIZE / 2) / TILESIZE;
//	printf("tile x right: %d, tile x left: %d, current y: %d, new_y: %d, tile y: %d\n", tile_x_right, tile_x_left, cube->p.position_y, new_y + (PLAYERSIZE / 2), tile_y);
	if (tile_x_right < 0 || tile_x_right >= cube->map.width || tile_x_left < 0 || tile_x_left >= cube->map.width
		|| tile_y < 0 || tile_y >= cube->map.height)
		return (true);
	return (cube->map.map[tile_y][tile_x_right] == 1
			|| cube->map.map[tile_y][tile_x_left] == 1
			|| cube->map.map[tile_y][tile_x_right] == 3
			|| cube->map.map[tile_y][tile_x_left] == 3);
}

bool	check_left_wall(t_cube *cube, int new_x)
{
	int	tile_x;
	int	tile_y_up;
	int	tile_y_down;

	tile_x = (new_x - PLAYERSIZE / 2) / TILESIZE;
	tile_y_up = (cube->p.position_y + PLAYERSIZE / 2) / TILESIZE;
	tile_y_down = (cube->p.position_y - PLAYERSIZE / 2) / TILESIZE;
	if (tile_x < 0 || tile_x >= cube->map.width || tile_y_up < 0 || tile_y_up >= cube->map.height
		|| tile_y_down < 0 || tile_y_down >= cube->map.height)
		return (true);
	return (cube->map.map[tile_y_up][tile_x] == 1
			|| cube->map.map[tile_y_down][tile_x] == 1
			|| cube->map.map[tile_y_up][tile_x] == 3
			|| cube->map.map[tile_y_down][tile_x] == 3);
}

bool	check_right_wall(t_cube *cube, int new_x)
{
	int	tile_x;
	int	tile_y_up;
	int	tile_y_down;

	tile_x = (new_x + PLAYERSIZE / 2) / TILESIZE;
	tile_y_up = (cube->p.position_y + PLAYERSIZE / 2) / TILESIZE;
	tile_y_down = (cube->p.position_y - PLAYERSIZE / 2) / TILESIZE;
	if (tile_x < 0 || tile_x >= cube->map.width || tile_y_up < 0 || tile_y_up >= cube->map.height
		|| tile_y_down < 0 || tile_y_down >= cube->map.height)
		return (true);	
	return (cube->map.map[tile_y_up][tile_x] == 1
			|| cube->map.map[tile_y_down][tile_x] == 1
			|| cube->map.map[tile_y_up][tile_x] == 3
			|| cube->map.map[tile_y_down][tile_x] == 3);
}

bool	check_wall_tile(t_cube *cube, int new_x, int new_y, int a)
{
	if (a == UP)
		return (check_up_wall(cube, new_y));
	if (a == DOWN)
		return (check_down_wall(cube, new_y));
	if (a == LEFT)
		return (check_left_wall(cube, new_x));
	if (a == RIGHT)
		return (check_right_wall(cube, new_x));
	return (false);
}
