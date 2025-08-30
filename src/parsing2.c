/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:15:54 by njung             #+#    #+#             */
/*   Updated: 2025/08/30 17:38:03 by aakerblo         ###   ########.fr       */
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

static void	init_parse_vars(t_parse *parse)
{
	parse->textures_done = 0;
	parse->map_row = 0;
	parse->texture_count = 0;
}

int	parse_map_file(int fd, t_cube *cube, char *filename)
{
	char	*line;
	int		result;
	t_parse	parse;

	init_parse_vars(&parse);
	line = get_next_line(fd);
	while (line)
	{
		if (handle_empty_line(line))
		{
			line = get_next_line(fd);
			continue ;
		}
		result = process_line(line, cube, filename, &parse);
		if (result == 0)
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}
