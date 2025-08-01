/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:38:57 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/01 19:41:09 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raycasting(t_cube *cube)
{
	double	angle;
	double	increment;
	
	if (DEBUG)
	{
		increment = RADIAN;
		angle = 0 - (FOV / 2);
		while (angle < FOV / 2)
		{
			draw_line(cube, angle);
			angle += increment;
		}
	}
	else
	{
		increment = FOV / WIDTH;
		angle = 0;
		while ()
	}
}
