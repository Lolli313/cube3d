/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <njung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:15:54 by njung             #+#    #+#             */
/*   Updated: 2025/09/24 14:32:58 by njung            ###   ########.fr       */
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
		printf("Error\nInvalid map format\n");
		return (0);
	}
	return (1);
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
			return (free(line), finish_file_reading(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	parse_game(int ac, char **argv, t_cube *cube)
{
	if (!load_map(ac, argv, cube))
		return (0);
	if (!validate_textures(&cube->map))
		return (0);
	if (!validate_map_content(cube))
		return (0);
	if (!validate_doors(cube))
		return (0);
	if (!validate_map_boundaries(cube))
		return (0);
	printf("Parsing completed successfully\n");
	return (1);
}
