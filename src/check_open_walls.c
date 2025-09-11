/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:59:27 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/11 14:10:32 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_open_north(t_map *map)
{
	int		x;
	int		y;
	bool	space;
	
	x = -1;
	while (++x < map->width)
	{
		space = false;
		y = map->height;
		while (--y >= 0)
		{
			if (map->map[y][x] == 0 || map->map[y][x] == 3)
				space = true;
			else if (map->map[y][x] == 1)
				space = false;
			else if (map->map[y][x] == 5 && space == true)
				return (1);
		}
		if (space == true)
			return (1);
	}
	return (0);	
}

static int	check_open_south(t_map *map)
{
	int		x;
	int		y;
	bool	space;
	
	x = -1;
	while (++x < map->width)
	{
		space = false;
		y = -1;
		while (++y < map->height)
		{
			if (map->map[y][x] == 0 || map->map[y][x] == 3)
				space = true;
			else if (map->map[y][x] == 1)
				space = false;
			else if (map->map[y][x] == 5 && space == true)
				return (1);
		}
		if (space == true)
			return (1);
	}
	return (0);	
}

static int	check_open_west(t_map *map)
{
	int		x;
	int		y;
	bool	space;
	
	y = -1;
	while (++y < map->height)
	{
		space = false;
		x = map->width;
		while (--x >= 0)
		{
			if (map->map[y][x] == 0 || map->map[y][x] == 3)
				space = true;
			else if (map->map[y][x] == 1)
				space = false;
			else if (map->map[y][x] == 5 && space == true)
				return (1);
		}
		if (space == true)
			return (1);
	}
	return (0);
}

static int	check_open_east(t_map *map)
{
	int		x;
	int		y;
	bool	space;
	
	y = -1;
	while (++y < map->height)
	{
		space = false;
		x = -1;
		while (++x < map->width)
		{
			if (map->map[y][x] == 0 || map->map[y][x] == 3)
				space = true;
			else if (map->map[y][x] == 1)
				space = false;
			else if (map->map[y][x] == 5 && space == true)
				return (1);
		}
		if (space == true)
			return (1);
	}
	return (0);
}

int	check_open_walls(int **visited, t_map *map)
{
	if (check_open_north(map))
		return (1);
	if (check_open_south(map))
		return (1);
	if (check_open_east(map))
		return (1);
	if (check_open_west(map))
		return (1);
	(void)visited;
	return (0);
}
