/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <njung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:15:54 by njung             #+#    #+#             */
/*   Updated: 2025/08/14 16:23:58 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	process_texture_line(char *line, t_cube *cube, int *texture_count)
{
	if (parse_texture_line(line, cube))
	{
		(*texture_count)++;
		return (1);
	}
	return (0);
}

int	validate_textures_complete(int texture_count)
{
	if (texture_count != 6)
	{
		printf("Error: Invalid map format\n");
		return (0);
	}
	return (1);
}

static int	handle_empty_line(char *line)
{
	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		return (1);
	}
	return (0);
}

static void	init_parse_vars(int *textures_done, int *map_row, int *texture_count) // thx norme
{
	*textures_done = 0;
	*map_row = 0;
	*texture_count = 0;
}

int parse_map_file(int fd, t_cube *cube)
{
	char *line;
	int textures_done;
	int map_row;
	int texture_count;
	int result;

	init_parse_vars(&textures_done, &map_row, &texture_count);
	while ((line = get_next_line(fd)))
	{
		if (handle_empty_line(line))
			continue;
//	printf("line is %s", line);
		result = process_line(line, cube, &textures_done, &texture_count, &map_row);
		if (result == 0)
		{
			free(line);
			return (0);
		}
		if (result == 1)
		{
			free(line);
			continue;
		}
		free(line);
	}
	return (1);
}
