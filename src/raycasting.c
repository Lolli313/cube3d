/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:38:57 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/09 12:58:02 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raycasting(t_cube *cube)
{
	double	plane_length;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	int		x;

	plane_length = FOV;
	plane_x = -cube->p.cam_y * plane_length;
	plane_y = cube->p.cam_x * plane_length;
	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2.0 * x / (double)WIDTH - 1.0;
		cube->coord.ray_dir_x = cube->p.cam_x + plane_x * camera_x;
		cube->coord.ray_dir_y = cube->p.cam_y + plane_y * camera_x;
		draw_ray(cube, x);
		x++;
	}
}
