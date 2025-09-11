/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:11:44 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/11 14:33:45 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_minimap_tile(t_cube *cube, int x, int y, int tile_size)
{
	int	temp_x;
	int	temp_y;

	temp_x = -1;
	temp_y = -1;
	while (++temp_y < tile_size)
	{
		temp_x = -1;
		while (++temp_x < tile_size)
			draw_pixel(&cube->img, x + temp_x, y + temp_y, cube->color);
	}
}

static void	draw_minimap_player(t_cube *cube, int tile_size)
{
	double	map_x;
	double	map_y;
	int		temp_x;
	int		temp_y;
	int		player_size;

	map_x = 5 + (cube->p.position_x * tile_size) / TILESIZE;
	map_y = 5 + (cube->p.position_y * tile_size) / TILESIZE;
	temp_y = -1;
	player_size = tile_size / 2;
	if (player_size < 2)
		player_size = 2;
	else if (player_size > 7)
		player_size = 7;
	while (++temp_y < player_size)
	{
		temp_x = -1;
		while (++temp_x < player_size)
			draw_pixel(&cube->img, map_x + temp_x, map_y + temp_y, BLUE);
	}
}

static void	draw_minimap_row(t_cube *cube, int map_y, int y,
			int tile_size)
{
	int	x;
	int	map_x;

	x = 5;
	map_x = -1;
	while (++map_x < cube->map.width)
	{
		if (cube->map.accessibility_map[map_y][map_x] == 1)
		{
			cube->color = WHITE;
			if (cube->map.map[map_y][map_x] == 1)
				cube->color = BLACK;
			else if (cube->map.map[map_y][map_x] == 3)
				cube->color = GREEN;
			else if (cube->map.map[map_y][map_x] == 4)
				cube->color = DARK_PINK;
			draw_minimap_tile(cube, x, y, tile_size);
		}
		x += tile_size;
	}
}

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	draw_minimap(t_cube *cube)
{
	int	y;
	int	map_y;
	int	tile_size;

	cube->map.accessibility_map = create_accessibility_map(cube);
	if (!cube->map.accessibility_map)
		return ;
	tile_size = MINIMAP_SIZE / max(cube->map.width, cube->map.height);
	y = 5;
	map_y = -1;
	while (++map_y < cube->map.height)
	{
		draw_minimap_row(cube, map_y, y, tile_size);
		y += tile_size;
	}
	free_accessibility_map(cube->map.accessibility_map, cube->map.height);
	draw_minimap_player(cube, tile_size);
}
