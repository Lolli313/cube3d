/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:11:44 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/29 15:40:11 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_minimap_tile(t_cube *cube, int x, int y, int color)
{
	int temp_x;
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
	int	temp_x;
	int	temp_y;

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

void	draw_minimap(t_cube *cube)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	x = 5;
	y = 5;
	map_y = -1;
	while (++map_y < cube->map.height)
	{
		map_x = -1;
		x = 5;
		while (++map_x < cube->map.width)
		{
			if (cube->map.map[map_y][map_x] == 1)
				draw_minimap_tile(cube, x, y, BLACK);
			else if (cube->map.map[map_y][map_x] == 0 || cube->map.map[map_y][map_x] == 2)
				draw_minimap_tile(cube, x, y, WHITE);
			else if (cube->map.map[map_y][map_x] == 3)
				draw_minimap_tile(cube, x, y, GREEN);
			else if (cube->map.map[map_y][map_x] == 4)
				draw_minimap_tile(cube, x, y, RED);
			x += 5;
		}
		y += 5;
	}
	draw_minimap_player(cube);
}
