/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:43:59 by njung             #+#    #+#             */
/*   Updated: 2025/09/01 11:48:15 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_name(char **argv)
{
	int	len;

	len = 0;
	if (!argv || !argv[1])
		printf("Error: Please put a valid map name\n");
	while (argv[1][len])
		len++;
	if (len < 5)
		printf("Error: Wrong file name\n");
	if (argv[1][len - 4] == '.' && argv[1][len - 3] == 'c' && argv[1][len
		- 2] == 'u' && argv[1][len - 1] == 'b')
		return (1);
	printf("Error: Wrong file name\n");
	return (0);
}

int	parse_rgb(char *line)
{
	char	**rgb_values;
	int		r;
	int		g;
	int		b;
	int		color;

	rgb_values = ft_split(line, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
		return (-1);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_matrix(rgb_values);
		printf("Error: Wrong RGB value(s)");
		return (-1);
	}
	color = (r << 16) | (g << 8) | b;
	free_matrix(rgb_values);
	return (color);
}

static int	parse_direction_texture(char *line, t_cube *cube)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		cube->map.no = load_textures(cube, line + 3);
		return (1);
	}
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		cube->map.so = load_textures(cube, line + 3);
		return (1);
	}
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		cube->map.we = load_textures(cube, line + 3);
		return (1);
	}
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		cube->map.ea = load_textures(cube, line + 3);
		return (1);
	}
	cube->map.door = load_textures(cube, "assets/glass_tile.xpm");
	if (!cube->map.door)
		return (1);
	return (0);
}

static int	parse_color_line(char *line, t_map *map)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		map->floor = parse_rgb(line + 2);
		return (map->floor != -1);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		map->ceiling = parse_rgb(line + 2);
		return (map->ceiling != -1);
	}
	return (0);
}

int	parse_texture_line(char *line, t_cube *cube)
{
	if (parse_direction_texture(line, cube))
		return (1);
	if (parse_color_line(line, &cube->map))
		return (1);
	return (0);
}
