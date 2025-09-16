/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_side.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:37:30 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/16 16:44:30 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static t_img	*check_wall_side_2(t_cube *cube)
{
	t_door	*door;

	door = find_door(cube);
	if (door != NULL)
		return (cube->map.door);
	if (cube->someyt.is_anim_wall)
		return (handle_someyt(cube));
	else if (cube->coord.side == 1)
	{
		if (cube->coord.ray_dir_y > 0)
			return (cube->map.so);
		else
			return (cube->map.no);
	}
	else
	{
		if (cube->coord.ray_dir_x > 0)
			return (cube->map.ea);
		else
			return (cube->map.we);
	}
}

void	check_wall_side(t_cube *cube, int *tex_height, int *tex_width)
{
	*tex_height = cube->map.door->height;
	*tex_width = cube->map.door->width;
	cube->coord.side_detailed = check_wall_side_2(cube);
	if (cube->coord.side_detailed == cube->map.so)
	{
		*tex_height = cube->map.so->height;
		*tex_width = cube->map.so->width;
	}
	else if (cube->coord.side_detailed == cube->map.no)
	{
		*tex_height = cube->map.no->height;
		*tex_width = cube->map.no->width;
	}
	else if (cube->coord.side_detailed == cube->map.we)
	{
		*tex_height = cube->map.we->height;
		*tex_width = cube->map.we->width;
	}
	else if (cube->coord.side_detailed == cube->map.ea)
	{
		*tex_height = cube->map.ea->height;
		*tex_width = cube->map.ea->width;
	}
}
