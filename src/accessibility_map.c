/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessibility_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:50:57 by njung             #+#    #+#             */
/*   Updated: 2025/08/29 17:47:24 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_row_to_zero(int *row, int width)
{
	int	j;

	j = 0;
	while (j < width)
	{
		row[j] = 0;
		j++;
	}
}

static int **allocate_accessibility_map(int width, int height)
{
	int **accessibility_map;
	int i;

	accessibility_map = malloc(sizeof(int *) * height);
	if (!accessibility_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		accessibility_map[i] = malloc(sizeof(int) * width);
		if (!accessibility_map[i])
		{
			while (--i >= 0)
				free(accessibility_map[i]);
			free(accessibility_map);
			return (NULL);
		}
		init_row_to_zero(accessibility_map[i], width);
		i++;
	}
	return (accessibility_map);
}

static void flood_fill_accessibility(t_cube *cube, int **accessibility_map, int x, int y)
{
    if (x < 0 || x >= cube->map.width || y < 0 || y >= cube->map.height)
        return;
    if (accessibility_map[y][x] == 1)
        return;
    if (cube->map.map[y][x] == 1 || cube->map.map[y][x] == 5)
        return;
    accessibility_map[y][x] = 1;
    flood_fill_accessibility(cube, accessibility_map, x + 1, y);
    flood_fill_accessibility(cube, accessibility_map, x - 1, y);
    flood_fill_accessibility(cube, accessibility_map, x, y + 1);
    flood_fill_accessibility(cube, accessibility_map, x, y - 1);
}

int **create_accessibility_map(t_cube *cube)
{
    int **accessibility_map;
    int player_x, player_y;
    accessibility_map = allocate_accessibility_map(cube->map.width, cube->map.height);
    if (!accessibility_map)
        return (NULL);
    player_x = cube->p.position_x / TILESIZE;
    player_y = cube->p.position_y / TILESIZE;
    flood_fill_accessibility(cube, accessibility_map, player_x, player_y);
    return (accessibility_map);
}

void free_accessibility_map(int **accessibility_map, int height)
{
    int i;
    
    if (!accessibility_map)
        return;
    
    i = 0;
    while (i < height)
    {
        free(accessibility_map[i]);
        i++;
    }
    free(accessibility_map);
}
