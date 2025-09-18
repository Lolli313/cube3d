/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessibility_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:50:57 by njung             #+#    #+#             */
/*   Updated: 2025/09/18 16:35:41 by aakerblo         ###   ########.fr       */
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

static int	**allocate_accessibility_map(int width, int height)
{
	int	**accessibility_map;
	int	i;

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

int	**create_accessibility_map(t_cube *cube)
{
	int	**accessibility_map;
	int	x;
	int	y;

	accessibility_map = allocate_accessibility_map(cube->map.width,
			cube->map.height);
	if (!accessibility_map)
		return (NULL);
	y = -1;
	while (++y < cube->map.height)
	{
		x = -1;
		while (++x < cube->map.width)
		{
			if (cube->map.map[y][x] != 1 && cube->map.map[y][x] != 5 && cube->map.map[y][x] != 6)
				accessibility_map[y][x] = 1;
		}
	}
	return (accessibility_map);
}

void	free_accessibility_map(int **accessibility_map, int height)
{
	int	i;

	if (!accessibility_map)
		return ;
	i = 0;
	while (i < height)
	{
		free(accessibility_map[i]);
		i++;
	}
	free(accessibility_map);
}
