/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:06:06 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/29 15:39:54 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	is_valid_map_pos(t_cube *cube, int x, int y)
{
	return (x >= 0 && x < cube->map.width && y >= 0 && y < cube->map.height);
}

static int	get_map_value(t_cube *cube, int x, int y)
{
	if (!is_valid_map_pos(cube, x, y))
		return (1);
	return (cube->map.map[y][x]);
}

void	open_door(t_cube *cube, int tile_x, int tile_y)
{
	if (is_valid_map_pos(cube, tile_x, tile_y))
		cube->map.map[tile_y][tile_x] = 4;
}

void	close_door(t_cube *cube, int tile_x, int tile_y)
{
	if (is_valid_map_pos(cube, tile_x, tile_y))
		cube->map.map[tile_y][tile_x] = 3;
}

void	handle_door_2(t_cube *cube, int tile_x, int tile_y)
{
	if (get_map_value(cube, tile_x + 1, tile_y) == 4)
		close_door(cube, tile_x + 1, tile_y);
	else if (get_map_value(cube, tile_x, tile_y + 1) == 4)
		close_door(cube, tile_x, tile_y + 1);
	else if (get_map_value(cube, tile_x - 1, tile_y) == 4)
		close_door(cube, tile_x - 1, tile_y);
	else if (get_map_value(cube, tile_x, tile_y - 1) == 4)
		close_door(cube, tile_x, tile_y - 1);
	else if (get_map_value(cube, tile_x + 1, tile_y + 1) == 4)
		close_door(cube, tile_x + 1, tile_y + 1);
	else if (get_map_value(cube, tile_x - 1, tile_y + 1) == 4)
		close_door(cube, tile_x - 1, tile_y + 1);
	else if (get_map_value(cube, tile_x + 1, tile_y - 1) == 4)
		close_door(cube, tile_x + 1, tile_y - 1);
	else if (get_map_value(cube, tile_x - 1, tile_y - 1) == 4)
		close_door(cube, tile_x - 1, tile_y - 1);
}

int	*get_key_pressed(void)
{
	static int	key_pressed = 0;

	return (&key_pressed);
}

void	handle_door(t_cube *cube)
{
	int	*key_pressed;
	int	tile_x;
	int	tile_y;

	key_pressed = get_key_pressed();
	if (cube->keys.e_pressed && !(*key_pressed))
	{
		*key_pressed = 1;
		tile_x = cube->p.position_x / TILESIZE;
		tile_y = cube->p.position_y / TILESIZE;
		if (get_map_value(cube, tile_x + 1, tile_y) == 3)
			open_door(cube, tile_x + 1, tile_y);
		else if (get_map_value(cube, tile_x, tile_y + 1) == 3)
			open_door(cube, tile_x, tile_y + 1);
		else if (get_map_value(cube, tile_x - 1, tile_y) == 3)
			open_door(cube, tile_x - 1, tile_y);
		else if (get_map_value(cube, tile_x, tile_y - 1) == 3)
			open_door(cube, tile_x, tile_y - 1);
		else if (get_map_value(cube, tile_x + 1, tile_y + 1) == 3)
			open_door(cube, tile_x + 1, tile_y + 1);
		else if (get_map_value(cube, tile_x - 1, tile_y + 1) == 3)
			open_door(cube, tile_x - 1, tile_y + 1);
		else if (get_map_value(cube, tile_x + 1, tile_y - 1) == 3)
			open_door(cube, tile_x + 1, tile_y - 1);
		else if (get_map_value(cube, tile_x - 1, tile_y - 1) == 3)
			open_door(cube, tile_x - 1, tile_y - 1);
		else
			handle_door_2(cube, tile_x, tile_y);
	}
	else if (!cube->keys.e_pressed)
		*key_pressed = 0;
}
