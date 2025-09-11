/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:09:15 by njung             #+#    #+#             */
/*   Updated: 2025/09/11 14:06:24 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	allocate_each_row(t_map *map)
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

static int	allocate_map(t_map *map)
{
	if (!map || map->height <= 0 || map->width <= 0)
	{
		printf("Error: Allocate_map: Invalid parameters\n");
		return (0);
	}
	map->map = malloc(sizeof(int *) * map->height);
	if (!map->map)
		return (0);
	if (!allocate_each_row(map))
		return (0);
	printf("Successfully allocated map %dx%d\n", map->width, map->height);
	return (1);
}

int	allocate_map_from_file(char *filename, t_cube *cube)
{
	int	fd1;
	int	fd2;

	fd1 = open(filename, O_RDONLY);
	if (fd1 < 0)
		return (0);
	cube->map.width = check_width(fd1);
	close(fd1);
	fd2 = open(filename, O_RDONLY);
	if (fd2 < 0)
		return (0);
	cube->map.height = check_height(fd2);
	close(fd2);
	if (!allocate_map(&cube->map))
		return (0);
	return (1);
}
