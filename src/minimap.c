/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:11:44 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/28 17:20:27 by aakerblo         ###   ########.fr       */
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

void	draw_minimap_space(t_cube *cube, int x, int y)
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
			draw_pixel(&cube->img, x + temp_x, y + temp_y, WHITE);
		}
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
	while (++map_y < MAP_Y)
	{
		map_x = -1;
		x = 5;
		while (++map_x < MAP_X)
		{
//			printf("map y is %d and map x is %d\n", map_y, map_x);
//			printf("y is %d and x is %d\n", y, x);
			if (cube->map.map[map_y][map_x] == 1)
				draw_minimap_tile(cube, x, y, BLACK);
			else if (cube->map.map[map_y][map_x] == 0 || cube->map.map[map_y][map_x] == 2)
				draw_minimap_tile(cube, x, y, WHITE);
			else if (cube->map.map[map_y][map_x] == 3)
				draw_minimap_tile(cube, x, y, GREEN);
			x += 5;
		}
		y += 5;
	}
//	(void)cube;
}
