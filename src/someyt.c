/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   someyt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:52:48 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/18 16:23:54 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*make_frame_path(int i)
{
    char	*prefix;
    char	*num;
    char	*suffix;
    char	*tmp;
    char	*result;

	prefix = "assets/someyt_gif/frame_";
	suffix = ".xpm";
    num = ft_itoa(i);
    tmp = ft_strjoin(prefix, num);
    free(num);
    result = ft_strjoin(tmp, suffix);
    free(tmp);
    return result;
}

void	init_someyt(t_cube *cube, int row, int col)
{
	int		i;
	char	*path;

	i = 0;
	cube->map.map[row][col] = 6;
	if (!cube->someyt.is_init)
	{
		cube->someyt.has_anim_wall = true;
		while (i < SOMEYT_FRAMES)
		{
			path = make_frame_path(i);
			cube->someyt.tex[i++] = load_textures(cube, path);
			free(path);
		}
	}
	cube->someyt.is_init = true;
}

t_img	*handle_someyt(t_cube *cube)
{
	int	frame;
	int	ms;
	
	ms = (int)((cube->someyt.new_time - cube->someyt.start_time) * 1000);
	frame = (ms / SOMEYT_INTERVAL) % SOMEYT_FRAMES;
	cube->someyt.current_tex = cube->someyt.tex[frame];
	return (cube->someyt.current_tex);
}
