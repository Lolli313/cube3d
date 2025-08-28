/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:06:06 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/28 15:59:39 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	open_door(t_cube *cube, int tile_x, int tile_y)
{
	cube->map.map[tile_y][tile_x] = 4;
}

void	close_door(t_cube *cube, int tile_x, int tile_y)
{
	cube->map.map[tile_y][tile_x] = 3;
}

void	handle_door_2(t_cube *cube, int tile_x, int tile_y)
{
	if (cube->map.map[tile_y][tile_x + 1] == 4)
		close_door(cube, tile_x + 1, tile_y);
	else if (cube->map.map[tile_y + 1][tile_x] == 4)
		close_door(cube, tile_x, tile_y + 1);
	else if (cube->map.map[tile_y][tile_x - 1] == 4)
		close_door(cube, tile_x - 1, tile_y);
	else if (cube->map.map[tile_y - 1][tile_x] == 4)
		close_door(cube, tile_x, tile_y - 1);
	else if (cube->map.map[tile_y + 1][tile_x + 1] == 4)
		close_door(cube, tile_x + 1, tile_y + 1);
	else if (cube->map.map[tile_y + 1][tile_x - 1] == 4)
		close_door(cube, tile_x - 1, tile_y + 1);
	else if (cube->map.map[tile_y - 1][tile_x + 1] == 4)
		close_door(cube, tile_x + 1, tile_y - 1);
	else if (cube->map.map[tile_y - 1][tile_x - 1] == 4)
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
		if (cube->map.map[tile_y][tile_x + 1] == 3)
			open_door(cube, tile_x + 1, tile_y);
		else if (cube->map.map[tile_y + 1][tile_x] == 3)
			open_door(cube, tile_x, tile_y + 1);
		else if (cube->map.map[tile_y][tile_x - 1] == 3)
			open_door(cube, tile_x - 1, tile_y);
		else if (cube->map.map[tile_y - 1][tile_x] == 3)
			open_door(cube, tile_x, tile_y - 1);
		else if (cube->map.map[tile_y + 1][tile_x + 1] == 3)
			open_door(cube, tile_x + 1, tile_y + 1);
		else if (cube->map.map[tile_y + 1][tile_x - 1] == 3)
			open_door(cube, tile_x - 1, tile_y + 1);
		else if (cube->map.map[tile_y - 1][tile_x + 1] == 3)
			open_door(cube, tile_x + 1, tile_y - 1);
		else if (cube->map.map[tile_y - 1][tile_x - 1] == 3)
			open_door(cube, tile_x - 1, tile_y - 1);
		else
			handle_door_2(cube, tile_x, tile_y);
	}
	else if (!cube->keys.e_pressed)
		*key_pressed = 0;
}
