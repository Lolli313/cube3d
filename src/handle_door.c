/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:06:06 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/30 18:15:45 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	handle_open_door(t_cube *cube, int tile_x, int tile_y)
{
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
}

void	handle_closed_door(t_cube *cube, int tile_x, int tile_y)
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
		handle_open_door(cube, tile_x, tile_y);
		handle_closed_door(cube, tile_x, tile_y);
	}
	else if (!cube->keys.e_pressed)
		*key_pressed = 0;
}
