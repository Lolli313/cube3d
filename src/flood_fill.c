/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:02:54 by njung             #+#    #+#             */
/*   Updated: 2025/09/11 14:20:48 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_valid_position(int x, int y, t_map *map)
{
	return (x >= 0 && x < map->width && y >= 0 && y < map->height);
}

static int	is_accessible(t_map *map_struct, int x, int y)
{
	if (!is_valid_position(x, y, map_struct))
		return (0);
	return (map_struct->map[y][x] == 0 || map_struct->map[y][x] == 2);
}

void	flood_fill_recursive(t_map *map_struct, int **visited,
		int x, int y)
{
	if (!is_accessible(map_struct, x, y) || visited[y][x])
		return ;
	visited[y][x] = 1;
	flood_fill_recursive(map_struct, visited, x + 1, y);
	flood_fill_recursive(map_struct, visited, x - 1, y);
	flood_fill_recursive(map_struct, visited, x, y + 1);
	flood_fill_recursive(map_struct, visited, x, y - 1);
}
