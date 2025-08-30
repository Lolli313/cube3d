/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:51:43 by njung             #+#    #+#             */
/*   Updated: 2025/08/30 18:32:50 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_external_wall(t_map *map, int x, int y)
{
	if (map->map[y][x] != 1)
		return (0);
	if (x == 0 || x == map->width - 1 || y == 0 || y == map->height - 1)
		return (1);
	if ((x > 0 && map->map[y][x - 1] == 0) || (x < map->width - 1
			&& map->map[y][x + 1] == 0))
		return (1);
	if ((y > 0 && map->map[y - 1][x] == 0) || (y < map->height - 1 && map->map[y
			+ 1][x] == 0))
		return (1);
	return (0);
}

int	check_player_on_external_wall(t_map *map, int player_x, int player_y)
{
	if (is_external_wall(map, player_x, player_y))
	{
		printf("Error: Player cannot be placed on external walls\n");
		return (1);
	}
	return (0);
}
