/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:54:54 by njung             #+#    #+#             */
/*   Updated: 2025/09/05 16:34:00 by njung            ###   ########.fr       */
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

int	check_arg(int ac)
{
	if (ac != 2)
	{
		printf("Error\n Choose a map\n");
		return (0);
	}
	return (1);
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

int	load_map_with_dimensions(char *filename, t_cube *cube)
{
	int	fd1;
	int	fd2;

	fd1 = open(filename, O_RDONLY);
	cube->map.width = check_width(fd1);
	close(fd1);
	fd2 = open(filename, O_RDONLY);
	cube->map.height = check_height(fd2);
	close(fd2);
	if (!allocate_map(&cube->map))
		return (0);
	return (1);
}

void	set_player_position(t_cube *cube, char direction, int row, int col)
{
	cube->map.map[row][col] = 2;
	if (direction == 'N')
		cube->p.player_direction = 3 * PI / 2;
	else if (direction == 'S')
		cube->p.player_direction = PI / 2;
	else if (direction == 'E')
		cube->p.player_direction = 0;
	else if (direction == 'W')
		cube->p.player_direction = PI;
	cube->p.cam_x = cos(cube->p.player_direction);
	cube->p.cam_y = sin(cube->p.player_direction);
	cube->p.position_x = (TILESIZE * col + TILESIZE / 2) + (PLAYERSIZE / 2);
	cube->p.position_y = (TILESIZE * row) + (PLAYERSIZE / 2);
	cube->p.precise_x = (double)cube->p.position_x;
	cube->p.precise_y = (double)cube->p.position_y;
	cube->p.error_x = 0.0;
	cube->p.error_y = 0.0;
	cube->p.square_x = row;
	cube->p.square_y = row;
}
