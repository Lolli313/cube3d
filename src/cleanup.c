/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:47:43 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/22 13:50:38 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_textures(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->map.EA->img_addr);
	free(cube->map.EA);
	mlx_destroy_image(cube->mlx, cube->map.WE->img_addr);
	free(cube->map.WE);
	mlx_destroy_image(cube->mlx, cube->map.NO->img_addr);
	free(cube->map.NO);
	mlx_destroy_image(cube->mlx, cube->map.SO->img_addr);
	free(cube->map.SO);
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
