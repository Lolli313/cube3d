/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:15:03 by njung             #+#    #+#             */
/*   Updated: 2025/08/13 11:55:41 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	handle_texture_phase(char *line, t_cube *cube, int *texture_count,
		int *textures_done)
{
	if (process_texture_line(line, cube, texture_count))
		return (1);
	if (!validate_textures_complete(*texture_count))
		return (0);
	*textures_done = 1;
	return (2);
}

int	process_line(char *line, t_cube *cube, int *textures_done,
		int *texture_count, int *map_row)
{
	int	result;

	if (!*textures_done)
	{
		result = handle_texture_phase(line, cube, texture_count, textures_done);
		if (result == 0)
			return (0);
		if (result == 1)
			return (1);
	}
	if (*textures_done)
		process_map_line(line, cube, map_row);
	return (2);
}

int	process_map_line(char *line, t_cube *cube, int *map_row)
{
	if (*map_row < MAP_Y)
	{
		parse_map_line(line, cube, *map_row);
		(*map_row)++;
		return (1);
	}
	return (0);
}

int	parse_map_line(char *line, t_cube *cube, int row)
{
	int	col;
	int	i;

	col = 0;
	i = 0;
	while (line[i] && col < MAP_X)
	{
		if (line[i] == '1')
			cube->map.map[row][col] = 1;
		else if (line[i] == '0')
			cube->map.map[row][col] = 0;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			cube->map.map[row][col] = 2;
			cube->p.position_x = col * TILESIZE + TILESIZE / 2;
			cube->p.position_y = row * TILESIZE + TILESIZE / 2;
			set_player_direction(cube, line[i]);
		}
		else
			cube->map.map[row][col] = 0;
		col++;
		i++;
	}
	return (1);
}

void	set_player_direction(t_cube *cube, char direction)
{
	if (direction == 'N')
		cube->p.player_direction = 3 * PI / 2;
	else if (direction == 'S')
		cube->p.player_direction = PI / 2;
	else if (direction == 'E')
		cube->p.player_direction = 0;
	else if (direction == 'W')
		cube->p.player_direction = PI;
}
