/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:38:19 by njung             #+#    #+#             */
/*   Updated: 2025/08/14 19:54:45 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_duplicates(int fd)
{
	char	*line;
	int		no_count;
	int		so_count;
	int		we_count;
	int		ea_count;
	int		f_count;
	int		c_count;

	init_texture_counters(&no_count, &so_count, &we_count, &ea_count);
	init_color_counters(&f_count, &c_count);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (!count_elements(line, &no_count, &so_count, &we_count, &ea_count,
				&f_count, &c_count))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (1);
}

int	check_and_increment(int *count, char *element_name)
{
	(*count)++;
	if (*count > 1)
	{
		printf("Error\nDuplicate %s\n", element_name);
		return (0);
	}
	return (1);
}

int	count_elements(char *line, int *no, int *so, int *we, int *ea, int *f,
		int *c)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (check_and_increment(no, "NO texture"));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (check_and_increment(so, "SO texture"));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (check_and_increment(we, "WE texture"));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (check_and_increment(ea, "EA texture"));
	else if (line[0] == 'F' && line[1] == ' ')
		return (check_and_increment(f, "F color"));
	else if (line[0] == 'C' && line[1] == ' ')
		return (check_and_increment(c, "C color"));
	return (1);
}
int	check_map_before_textures(int texture_count, char first_char)
{
	if (texture_count < 6 && is_map_element(first_char))
	{
		printf("Error\nMap found before all textures defined\n");
		return (0);
	}
	return (1);
}

int	check_map_characters(char *line)
{
	int i;
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' || line[i] != '0' || line[i] != 'N' || line[i] != 'S'
			|| line[i] != 'E' || line[i] != 'W' || line[i] != ' ')
		{
			printf("Error\nMap invalid (wrong character)");
			return (0);
		}
	}
	return (1);
}