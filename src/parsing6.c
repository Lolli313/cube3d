/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:38:19 by njung             #+#    #+#             */
/*   Updated: 2025/08/30 17:10:25 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_duplicates(int fd)
{
	char	*line;
	t_count	count;

	init_counters(&count);
	line = get_next_line(fd);
	while ((line))
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else if (!count_elements(line, &count))
		{
			free(line);
			line = get_next_line(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	check_and_increment(int count, char *element_name)
{
	count++;
	if (count > 1)
	{
		printf("Error: Duplicate %s\n", element_name);
		return (0);
	}
	return (1);
}

int	count_elements(char *line, t_count *count)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (check_and_increment(count->no_count, "NO texture"));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (check_and_increment(count->so_count, "SO texture"));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (check_and_increment(count->we_count, "WE texture"));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (check_and_increment(count->ea_count, "EA texture"));
	else if (line[0] == 'F' && line[1] == ' ')
		return (check_and_increment(count->f_count, "F color"));
	else if (line[0] == 'C' && line[1] == ' ')
		return (check_and_increment(count->c_count, "C color"));
	return (1);
}

int	check_map_before_textures(int texture_count, char first_char)
{
	if (texture_count < 6 && is_map_element(first_char))
	{
		printf("Error: Map found before all textures defined\n");
		return (0);
	}
	return (1);
}

int	check_map_characters(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\n' && line[i] != 'D')
		{
			printf("Error: Map invalid (wrong character)\n");
			return (0);
		}
		i++;
	}
	return (1);
}
