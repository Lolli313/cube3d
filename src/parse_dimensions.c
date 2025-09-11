/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dimensions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:54:54 by njung             #+#    #+#             */
/*   Updated: 2025/09/11 14:05:01 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_width(int fd)
{
	char	*line;
	int		max_width;
	int		map_started;

	max_width = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' || line[0] != '\0')
		{
			if (!map_started && (line[0] == '1' || line[0] == '0'
					|| line[0] == ' '))
				map_started = 1;
			else if (map_started)
				assign_max_width(line, &max_width);
		}
		free(line);
		line = get_next_line(fd);
	}
	printf("DEBUG check_width: max_width = %d\n", max_width);
	return (max_width);
}

int	check_height(int fd)
{
	char	*line;
	int		map_started;
	int		height;

	map_started = 0;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!map_started && (line[0] == '0' || line[0] == '1'
				|| line[0] == ' '))
			map_started = 1;
		if (map_started)
			height++;
		free(line);
		line = get_next_line(fd);
	}
	printf("DEBUG check_height: height = %d\n", height);
	return (height);
}
