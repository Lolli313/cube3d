/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:11:44 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/30 19:07:32 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_minimap_tile(t_cube *cube, int x, int y, int color)
{
	int	temp_x;
	int	temp_y;

	temp_x = -1;
	temp_y = -1;
	while (++temp_y < 5)
	{
		temp_x = -1;
		while (++temp_x < 5)
		{
			draw_pixel(&cube->img, x + temp_x, y + temp_y, color);
		}
	}
}

void	draw_minimap_player(t_cube *cube)
{
	double	map_x;
	double	map_y;
	int		temp_x;
	int		temp_y;

	map_x = 5 + (cube->p.position_x * 5) / TILESIZE;
	map_y = 5 + (cube->p.position_y * 5) / TILESIZE;
	temp_y = -1;
	while (++temp_y < 3)
	{
		temp_x = -1;
		while (++temp_x < 3)
			draw_pixel(&cube->img, map_x + temp_x, map_y + temp_y, BLUE);
	}
}

void	draw_minimap_row(t_cube *cube, int map_y, int y,
			int **accessibility_map)
{
	int	x;
	int	map_x;

	x = 5;
	map_x = -1;
	while (++map_x < cube->map.width)
	{
		if (accessibility_map[map_y][map_x] == 1)
		{
			if (cube->map.map[map_y][map_x] == 1)
				draw_minimap_tile(cube, x, y, BLACK);
			else if (cube->map.map[map_y][map_x] == 0
				|| cube->map.map[map_y][map_x] == 2)
				draw_minimap_tile(cube, x, y, WHITE);
			else if (cube->map.map[map_y][map_x] == 3)
				draw_minimap_tile(cube, x, y, GREEN);
			else if (cube->map.map[map_y][map_x] == 4)
				draw_minimap_tile(cube, x, y, DARK_PINK);
		}
		x += 5;
	}
}

void	draw_minimap(t_cube *cube)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;
	int	**accessibility_map;

	accessibility_map = create_accessibility_map(cube);
	if (!accessibility_map)
		return ;
	x = 5;
	y = 5;
	map_y = -1;
	while (++map_y < cube->map.height)
	{
		map_x = -1;
		x = 5;
		draw_minimap_row(cube, map_y, y, accessibility_map);
		y += 5;
	}
	free_accessibility_map(accessibility_map, cube->map.height);
	draw_minimap_player(cube);
}
