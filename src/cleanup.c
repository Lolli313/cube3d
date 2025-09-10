/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:47:43 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/10 16:23:27 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_textures(t_cube *cube)
{
	if (cube->map.ea)
	{
		mlx_destroy_image(cube->mlx, cube->map.ea->img_addr);
		free(cube->map.ea);
	}
	if (cube->map.we)
	{
		mlx_destroy_image(cube->mlx, cube->map.we->img_addr);
		free(cube->map.we);
	}
	if (cube->map.no)
	{
		mlx_destroy_image(cube->mlx, cube->map.no->img_addr);
		free(cube->map.no);
	}
	if (cube->map.so)
	{
		mlx_destroy_image(cube->mlx, cube->map.so->img_addr);
		free(cube->map.so);
	}
	if (cube->map.door)
	{
		mlx_destroy_image(cube->mlx, cube->map.door->img_addr);
		free(cube->map.door);
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->height)
	{
		while (i < map->height)
			free(map->map[i++]);
		free(map->map);
	}
}

void	free_doors(t_door *door)
{
	t_door	*temp;

	if (door)
	{
		temp = door->next;
		while (door)
		{
			free(door);
			door = temp;
		}
	}
}

int	cleanup(t_cube *cube)
{
	free_textures(cube);
	free_map(&cube->map);
	free_doors(cube->door);
	mlx_destroy_image(cube->mlx, cube->img.img_addr);
	mlx_destroy_window(cube->mlx, cube->mlx_win);
#ifdef __linux__
	mlx_destroy_display(cube->mlx);
#endif
	free(cube->mlx);
	exit(0);
}
