/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:53:00 by njung             #+#    #+#             */
/*   Updated: 2025/09/11 14:56:30 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*create_map_path(char *map_name)
{
	int		i;
	int		j;
	int		name_len;
	char	*full_path;

	name_len = 0;
	while (map_name[name_len])
		name_len++;
	full_path = malloc(sizeof(char) * (5 + name_len + 1));
	if (!full_path)
		return (NULL);
	full_path[0] = 'm';
	full_path[1] = 'a';
	full_path[2] = 'p';
	full_path[3] = 's';
	full_path[4] = '/';
	i = 5;
	j = 0;
	while (map_name[j])
		full_path[i++] = map_name[j++];
	full_path[i] = '\0';
	return (full_path);
}

static int	find_map(int ac, char **argv)
{
	char	*map_path;
	int		fd;

	if (check_name(argv) && check_arg(ac))
	{
		map_path = create_map_path(argv[1]);
		fd = open(map_path, O_RDONLY);
		if (!map_path || fd == -1)
		{
			printf("Error: Map not found\n");
			if (fd == -1)
				free(map_path);
			return (-1);
		}
		free(map_path);
		return (fd);
	}
	return (-1);
}

static int	validate_file_checks(int ac, char **argv)
{
	int	fd;

	fd = find_map(ac, argv);
	if (fd < 0)
		return (0);
	if (!check_duplicates(fd))
	{
		close(fd);
		return (0);
	}
	close(fd);
	fd = find_map(ac, argv);
	if (fd < 0)
		return (0);
	if (!validate_element_order(fd))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	load_map(int ac, char **argv, t_cube *cube)
{
	int		fd;
	char	*map_path;

	if (!validate_file_checks(ac, argv))
		return (0);
	fd = find_map(ac, argv);
	if (fd < 0)
		return (0);
	map_path = create_map_path(argv[1]);
	if (!map_path)
	{
		close(fd);
		return (0);
	}
	if (!parse_map_file(fd, cube, map_path))
	{
		close(fd);
		free(map_path);
		return (0);
	}
	close(fd);
	free(map_path);
	return (1);
}
