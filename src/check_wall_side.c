/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_side.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:37:30 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/26 16:04:01 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_img	*check_wall_side_2(t_cube *cube)
{
	t_door	*door;

	door = find_door(cube);
	if (door != NULL)
		return (cube->map.door);
	if (cube->coord.side == 1)
	{
		if (cube->coord.ray_dir_y > 0)
			return (cube->map.SO);
		else
			return (cube->map.NO);
	}
	else
	{
		if (cube->coord.ray_dir_x > 0)
			return (cube->map.EA);
		else
			return (cube->map.WE);
	}
}

void	check_wall_side(t_cube *cube, int *tex_height, int *tex_width)
{
	cube->coord.side_detailed = check_wall_side_2(cube);
	if (cube->coord.side_detailed == cube->map.SO)
	{
		*tex_height = cube->map.SO->height;
		*tex_width = cube->map.SO->width;
	}
	else if (cube->coord.side_detailed == cube->map.NO)
	{
		*tex_height = cube->map.NO->height;
		*tex_width = cube->map.NO->width;
	}
	else if (cube->coord.side_detailed == cube->map.WE)
	{
		*tex_height = cube->map.WE->height;
		*tex_width = cube->map.WE->width;
	}
	else if (cube->coord.side_detailed == cube->map.EA)
	{
		*tex_height = cube->map.EA->height;
		*tex_width = cube->map.EA->width;
	}
	else
	{
		*tex_height = cube->map.door->height;
		*tex_width = cube->map.door->width;
	}
}
