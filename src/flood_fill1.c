/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:02:39 by njung             #+#    #+#             */
/*   Updated: 2025/08/25 18:04:04 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_visited_map(int visited[MAP_Y][MAP_X])
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_Y)
	{
		x = 0;
		while (x < MAP_X)
		{
			visited[y][x] = 0;
			x++;
		}
		y++;
	}
}

int	find_player_position(int map[MAP_Y][MAP_X], int *player_x, int *player_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_Y)
	{
		x = 0;
		while (x < MAP_X)
		{
			if (map[y][x] == 2)
			{
				*player_x = x;
				*player_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_player_on_border(int player_x, int player_y)
{
	if (player_x == 0 || player_x == MAP_X - 1)
		return (1);
	if (player_y == 0 || player_y == MAP_Y - 1)
		return (1);
	return (0);
}

int	validate_map_boundaries(t_cube *cube)
{
	int	visited[MAP_Y][MAP_X];
	int	player_x;
	int	player_y;

	if (!find_player_position(cube->map.map, &player_x, &player_y))
		return (0);
	if (check_player_on_border(player_x, player_y))
	{
		printf("Error: Player is on map border\n");
		return (0);
	}
	if (check_player_on_external_wall(cube->map.map, player_x, player_y))
		return (0);
	init_visited_map(visited);
	flood_fill_recursive(cube->map.map, visited, player_x, player_y);
	if (is_border_accessible(visited))
	{
		printf("Error: Map is not enclosed by walls\n");
		return (0);
	}
	return (1);
}
