/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:47:34 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/25 17:10:26 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_img	*load_textures(t_cube *cube, char *path_plus_newline)
{
	t_img	*img;
	char	*path;

	path = ft_strtrim(path_plus_newline, " \n\r\t");
	if (!check_xpm_extension(path))
		return (free(path), NULL);
	if (!check_texture_file(path))
		return (free(path), NULL);
	img = malloc(sizeof(t_img));
	if (!img)
	{
		printf("Error: While loading texture\n");
		return (free(path), NULL);
	}
	img->img_addr = mlx_xpm_file_to_image(cube->mlx, path, &img->width,
			&img->height);
	if (img->img_addr == NULL)
	{
		printf("Error: While loading texture\n");
		free(img);
		return (free(path), NULL);
	}
	img->pixel_addr = mlx_get_data_addr(img->img_addr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (free(path), img);
}

int	get_texture_pixel(t_img *img, int x, int y)
{
	char	*dst;
	int		color;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	dst = img->pixel_addr + (y * img->line_length + x * (img->bits_per_pixel
				/ 8));
	color = *(unsigned int *)dst;
	return (color);
}
