/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <njung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:15:03 by njung             #+#    #+#             */
/*   Updated: 2025/09/24 14:32:58 by njung            ###   ########.fr       */
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

int	process_order_line(char *line, int *texture_count, int *map_started)
{
	if (line[0] == '\n' || line[0] == '\0')
		return (1);
	if (!*map_started && is_texture_element(line[0]))
	{
		(*texture_count)++;
		return (1);
	}
	if (!check_map_before_textures(*texture_count, line[0]))
		return (0);
	*map_started = 1;
	return (1);
}

static int	parse_map_line(char *line, t_cube *cube, int row)
{
	int	col;
	int	i;

	col = 0;
	i = 0;
	while (col < cube->map.width)
	{
		if (line[i] == '1')
			cube->map.map[row][col] = 1;
		else if (line[i] == '0')
			cube->map.map[row][col] = 0;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			set_player_position(cube, line[i], row, col);
		else if (line[i] == 'D')
			parse_door(cube, row, col);
		else if (line[i] == 'R')
			init_someyt(cube, row, col);
		else
			cube->map.map[row][col] = 5;
		col++;
		if (line[i])
			i++;
	}
	return (1);
}

static int	process_map_line(char *line, t_cube *cube, int *map_row)
{
	if (!check_map_characters(line))
		return (0);
	if (*map_row < MAP_Y)
	{
		parse_map_line(line, cube, *map_row);
		(*map_row)++;
		return (1);
	}
	printf("Error\nMap too big\n");
	return (0);
}

int	process_line(char *line, t_cube *cube, char *filename, t_parse *parse)
{
	int	result;

	if (!parse->textures_done)
	{
		result = handle_texture_phase(line, cube, &parse->texture_count,
				&parse->textures_done);
		if (result == 0)
			return (0);
		if (result == 1)
			return (1);
		if (result == 2 && !allocate_map_from_file(filename, cube))
			return (0);
	}
	if (parse->textures_done)
	{
		if (!process_map_line(line, cube, &parse->map_row))
			return (0);
	}
	return (2);
}
