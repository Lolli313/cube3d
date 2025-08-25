/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:02:54 by njung             #+#    #+#             */
/*   Updated: 2025/08/25 18:03:04 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_valid_position(int x, int y)
{
	return (x >= 0 && x < MAP_X && y >= 0 && y < MAP_Y);
}

int	is_accessible(int map[MAP_Y][MAP_X], int x, int y)
{
	if (!is_valid_position(x, y))
		return (0);
	return (map[y][x] == 0 || map[y][x] == 2);
}

int	is_border_accessible(int visited[MAP_Y][MAP_X])
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_Y)
	{
		if ((y == 0 || y == MAP_Y - 1))
		{
			x = 0;
			while (x < MAP_X)
			{
				if (visited[y][x])
					return (1);
				x++;
			}
		}
		else
		{
			if (visited[y][0] || visited[y][MAP_X - 1])
				return (1);
		}
		y++;
	}
	return (0);
}

void	flood_fill_recursive(int map[MAP_Y][MAP_X], int visited[MAP_Y][MAP_X],
		int x, int y)
{
	if (!is_accessible(map, x, y) || visited[y][x])
		return ;
	visited[y][x] = 1;
	flood_fill_recursive(map, visited, x + 1, y);
	flood_fill_recursive(map, visited, x - 1, y);
	flood_fill_recursive(map, visited, x, y + 1);
	flood_fill_recursive(map, visited, x, y - 1);
}
