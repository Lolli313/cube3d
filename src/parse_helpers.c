/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <njung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:48:33 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/24 14:32:58 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	finish_file_reading(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	assign_max_width(char *line, int *max_width)
{
	int	current_width;

	current_width = 0;
	current_width = ft_strlen(line);
	if (line[current_width - 1] == '\n')
		current_width--;
	if (current_width > *max_width)
		*max_width = current_width;
}

int	handle_empty_line(char *line)
{
	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		return (1);
	}
	return (0);
}

int	check_arg(int ac)
{
	if (ac != 2)
	{
		printf("Error\nChoose a map\n");
		return (0);
	}
	return (1);
}

int	check_name(char **argv)
{
	int	len;

	len = 0;
	if (!argv || !argv[1])
		printf("Error\nPlease put a valid map name\n");
	while (argv[1][len])
		len++;
	if (len < 5)
		printf("Error\nWrong file name\n");
	if (argv[1][len - 4] == '.' && argv[1][len - 3] == 'c' && argv[1][len
		- 2] == 'u' && argv[1][len - 1] == 'b')
		return (1);
	printf("Error\nWrong file name\n");
	return (0);
}
