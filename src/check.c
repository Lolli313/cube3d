/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:59:26 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/09 13:01:19 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	check_wall_tile(t_cube *cube, int new_x, int new_y, int a)
{
	int	tile_x;
	int	tile_y;
	int	tile_x2;
	int	tile_y2;
	
	if (a == LEFT)
	{
		tile_x = new_x / TILESIZE;
		tile_y = cube->p.position_y / TILESIZE;
		tile_y2 = (cube->p.position_y + PLAYERSIZE - 1) / TILESIZE;
		if (tile_x < 0 || tile_x >= MAP_X || tile_y < 0 || tile_y >= MAP_Y || tile_y2 < 0 || tile_y2 >= MAP_Y)
			return (true);
		return (cube->map.map[tile_y][tile_x] == 1 || cube->map.map[tile_y2][tile_x] == 1);
	}
	if (a == RIGHT)
	{
		tile_x = (new_x + PLAYERSIZE) / TILESIZE;
		tile_y = cube->p.position_y / TILESIZE;
		tile_y2 = (cube->p.position_y + PLAYERSIZE - 1) / TILESIZE;
		if (tile_x < 0 || tile_x >= MAP_X || tile_y < 0 || tile_y >= MAP_Y || tile_y2 < 0 || tile_y2 >= MAP_Y)
			return (true);
		return (cube->map.map[tile_y][tile_x] == 1 || cube->map.map[tile_y2][tile_x] == 1);
	}
	if (a == UP)
	{
		tile_x = cube->p.position_x / TILESIZE;
		tile_x2 = (cube->p.position_x + PLAYERSIZE - 1) / TILESIZE;
		tile_y = new_y / TILESIZE;
		if (tile_x < 0 || tile_x >= MAP_X || tile_x2 < 0 || tile_x2 >= MAP_X || tile_y < 0 || tile_y >= MAP_Y)
			return (true);
		return (cube->map.map[tile_y][tile_x] == 1 || cube->map.map[tile_y][tile_x2] == 1);
	}
	if (a == DOWN)
	{
		tile_x = cube->p.position_x / TILESIZE;
		tile_x2 = (cube->p.position_x + PLAYERSIZE - 1) / TILESIZE;
		tile_y = (new_y + PLAYERSIZE) / TILESIZE;
		if (tile_x < 0 || tile_x >= MAP_X || tile_x2 < 0 || tile_x2 >= MAP_X || tile_y < 0 || tile_y >= MAP_Y)
			return (true);
		return (cube->map.map[tile_y][tile_x] == 1 || cube->map.map[tile_y][tile_x2] == 1);
	}
	return (false);
}
