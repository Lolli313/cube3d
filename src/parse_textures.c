/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:43:59 by njung             #+#    #+#             */
/*   Updated: 2025/09/11 18:13:40 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static bool	rgb_digit_check(char *rgb_value)
{
	int	i;

	i = 0;
	while (rgb_value[i] == ' ')
		i++;
	if (!ft_isdigit(rgb_value[i]))
		return (false);
	while (rgb_value[i])
	{
		if (!ft_isdigit(rgb_value[i]) && rgb_value[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

static int	parse_rgb(char *line)
{
	char	**rgb_values;
	int		r;
	int		g;
	int		b;
	int		color;

	rgb_values = ft_split(line, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
		return (printf("Error: Wrong RGB value(s)\n"), -1);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (!rgb_digit_check(rgb_values[0]) || (ft_strlen(rgb_values[0]) > 3 && !rgb_digit_check(rgb_values[0])) || r < 0 || r > 255
		|| !rgb_digit_check(rgb_values[1]) || (ft_strlen(rgb_values[1]) > 3 && !rgb_digit_check(rgb_values[1])) || g < 0 || g > 255
		|| !rgb_digit_check(rgb_values[2]) || (ft_strlen(rgb_values[2]) > 3 && !rgb_digit_check(rgb_values[2])) || b < 0 || b > 255 || rgb_values[3])
	{
		free_matrix(rgb_values);
		printf("Error: Wrong RGB value(s)\n");
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
	else if (!cube->map.door)
		cube->map.door = load_textures(cube, DOOR_TEXTURE);
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
