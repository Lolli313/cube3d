/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <njung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:02:39 by njung             #+#    #+#             */
/*   Updated: 2025/09/24 14:32:58 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	find_player_position(t_map *map, int *player_x, int *player_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 2)
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

static int	check_player_on_border(int player_x, int player_y, t_map *map)
{
	if (player_x == 0 || player_x == map->width - 1)
		return (1);
	if (player_y == 0 || player_y == map->height - 1)
		return (1);
	return (0);
}

static int	**allocate_visited_map(t_map *map)
{
	int	**visited;
	int	i;

	visited = malloc(sizeof(int *) * map->height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		visited[i] = malloc(sizeof(int) * map->width);
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

static void	free_visited_map(int **visited, int height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	validate_map_boundaries(t_cube *cube)
{
	int	**visited;
	int	player_x;
	int	player_y;

	if (!find_player_position(&cube->map, &player_x, &player_y))
		return (0);
	if (check_player_on_border(player_x, player_y, &cube->map))
	{
		printf("Error\nPlayer is on map border\n");
		return (0);
	}
	if (check_player_on_external_wall(&cube->map, player_x, player_y))
		return (0);
	visited = allocate_visited_map(&cube->map);
	if (!visited)
		return (0);
	init_visited_map(visited, &cube->map);
	flood_fill_recursive(&cube->map, visited, player_x, player_y);
	if (check_open_walls(visited, &cube->map))
	{
		free_visited_map(visited, cube->map.height);
		return (printf("Error\nMap is not enclosed by walls\n"), 0);
	}
	free_visited_map(visited, cube->map.height);
	return (1);
}
