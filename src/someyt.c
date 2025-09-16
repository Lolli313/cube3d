/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   someyt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:52:48 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/16 17:11:33 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_someyt(t_cube *cube, int row, int col)
{
	cube->someyt.has_anim_wall = true;
	cube->map.map[row][col] = 6;
	if (!cube->someyt.tex_1)
		cube->someyt.tex_1 = load_textures(cube, "assets/ssrun_blue.xpm");
	if (!cube->someyt.tex_2)
		cube->someyt.tex_2 = load_textures(cube, "assets/ssrun_green.xpm");
	if (!cube->someyt.tex_3)
		cube->someyt.tex_3 = load_textures(cube, "assets/ssrun_red.xpm");
	if (!cube->someyt.tex_4)
		cube->someyt.tex_4 = load_textures(cube, "assets/ssrun_yellow.xpm");
}

t_img	*handle_someyt(t_cube *cube)
{
	int	frame;
	int	ms;
	
	ms = (int)((cube->someyt.new_time - cube->someyt.start_time) * 1000);
	frame = (ms / SOMEYT_INTERVAL) % 4;
//	printf("new time is %f\n", cube->someyt.new_time);
//	printf("frame value is %d\n", frame);
	if (frame == 0)
		cube->someyt.current_tex = cube->someyt.tex_1;
	else if (frame == 1)
		cube->someyt.current_tex = cube->someyt.tex_2;
	else if (frame == 2)
		cube->someyt.current_tex = cube->someyt.tex_3;
	else if (frame == 3)
		cube->someyt.current_tex = cube->someyt.tex_4;
	return (cube->someyt.current_tex);
}
