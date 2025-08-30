/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:56:12 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/30 17:57:41 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	is_valid_map_pos(t_cube *cube, int x, int y)
{
	return (x >= 0 && x < cube->map.width && y >= 0 && y < cube->map.height);
}

int	get_map_value(t_cube *cube, int x, int y)
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

int	*get_key_pressed(void)
{
	static int	key_pressed = 0;

	return (&key_pressed);
}
