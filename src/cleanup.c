/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:47:43 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/01 11:48:15 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_textures(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->map.ea->img_addr);
	free(cube->map.ea);
	mlx_destroy_image(cube->mlx, cube->map.we->img_addr);
	free(cube->map.we);
	mlx_destroy_image(cube->mlx, cube->map.no->img_addr);
	free(cube->map.no);
	mlx_destroy_image(cube->mlx, cube->map.so->img_addr);
	free(cube->map.so);
}

int	cleanup(t_cube *cube)
{
	free_textures(cube);
	mlx_destroy_window(cube->mlx, cube->mlx_win);
	mlx_destroy_image(cube->mlx, cube->img.img_addr);
#ifdef __linux__
	mlx_destroy_display(cube->mlx);
#endif
	free(cube->mlx);
	exit(0);
}
