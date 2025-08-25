/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:51:43 by njung             #+#    #+#             */
/*   Updated: 2025/08/25 18:03:09 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_external_wall(int map[MAP_Y][MAP_X], int x, int y)
{
	if (map[y][x] != 1)
		return (0);
	if (x == 0 || x == MAP_X - 1 || y == 0 || y == MAP_Y - 1)
		return (1);
	if ((x > 0 && map[y][x - 1] == 0) || (x < MAP_X - 1 && map[y][x + 1] == 0))
		return (1);
	if ((y > 0 && map[y - 1][x] == 0) || (y < MAP_Y - 1 && map[y + 1][x] == 0))
		return (1);
	return (0);
}

int	check_player_on_external_wall(int map[MAP_Y][MAP_X], int player_x, 
		int player_y)
{
	if (is_external_wall(map, player_x, player_y))
	{
		printf("Error: Player cannot be placed on external walls\n");
		return (1);
	}
	return (0);
}