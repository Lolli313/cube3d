/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:54:54 by njung             #+#    #+#             */
/*   Updated: 2025/08/29 15:41:34 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int check_width(int fd)
{
    char    *line;
    int     max_width;
    int     current_width;
    int     map_started;

    max_width = 0;
    map_started = 0;
    while ((line = get_next_line(fd)))
    {
        if (line[0] == '\n' || line[0] == '\0')
        {
            free(line);
            continue;
        }
        if (!map_started && (line[0] == '1' || line[0] == '0' || line[0] == ' '))
            map_started = 1;
        if (map_started)
        {
            current_width = ft_strlen(line);
            if (line[current_width - 1] == '\n')
                current_width--;
            if (current_width > max_width)
                max_width = current_width;
        }
        free(line);
    }
    return (max_width);
}

int check_height(int fd)
{
    char *line;
    int map_started;
    int height;

    map_started = 0;
    height = 0;
    while ((line = get_next_line(fd)))
    {
        if (line[0] == ' ' || line[0] == '\n')
        {
            free(line);
            continue;
        }
        if (!map_started && (line[0] == '0' || line[0] == '1' || line[0] == ' '))
            map_started = 1;
        if (map_started)
        {
            height++;
        }
        free(line);
    }
    return (height);
}

int load_map_with_dimensions(char *filename, t_cube *cube)
{
    int fd1;
    int fd2;

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