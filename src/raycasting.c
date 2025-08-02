/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:38:57 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/02 17:37:58 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raycasting(t_cube *cube)
{
	double	angle;
	double	increment;
	int		cutoff_angle;

	if (DEBUG)
	{
		cutoff_angle = FOV / 2;
		increment = RADIAN;
		angle = 0 - cutoff_angle;
		while (angle < cutoff_angle)
		{
			draw_line(cube, angle, cutoff_angle);
			angle += increment;
		}
	}
	else
	{
		increment = FOV / WIDTH;
		angle = 0;
		cutoff_angle = 0;
		while (cutoff_angle < WIDTH)
		{
			draw_line(cube, angle, cutoff_angle);
			angle += increment;
			cutoff_angle += 1;
		}
	}
}
