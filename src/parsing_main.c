/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:09:15 by njung             #+#    #+#             */
/*   Updated: 2025/09/06 13:42:01 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	allocate_each_row(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(int) * map->width);
		if (!map->map[i])
		{
			while (--i >= 0)
				free(map->map[i]);
			free(map->map);
			map->map = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

int	allocate_map(t_map *map)
{
	if (!map || map->height <= 0 || map->width <= 0)
	{
		printf("DEBUG allocate_map: Invalid parameters - ");
		if (map)
			printf("height=%d, width=%d\n", map->height, map->width);
		else
			printf("height=%d, width=%d\n", -1, -1);
		return (0);
	}
	printf("DEBUG allocate_map: Allocating map %dx%d\n", map->width,
		map->height);
	map->map = malloc(sizeof(int *) * map->height);
	if (!map->map)
		return (0);
	if (!allocate_each_row(map))
		return (0);
	printf("DEBUG allocate_map: Successfully allocated map %dx%d\n", map->width,
		map->height);
	return (1);
}

int	parse_game(int ac, char **argv, t_cube *cube)
{
	if (!load_map(ac, argv, cube))
	{
		printf("Error\n Failed to load map\n");
		return (0);
	}
	if (!validate_textures(&cube->map))
		return (0);
	if (!validate_map_content(cube))
		return (0);
	if (!validate_doors(cube))
		return (0);
	if (!validate_map_boundaries(cube))
		return (0);
	printf("Parsing completed successfully\n");
	return (1);
}
