/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <njung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:53:00 by njung             #+#    #+#             */
/*   Updated: 2025/08/07 16:45:00 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char *create_map_path(char *map_name)
{
    int i, j;
    int maps_len = 5;
    int name_len = 0;
    char *full_path;

    while (map_name[name_len])
        name_len++;
    full_path = malloc(sizeof(char) * (maps_len + name_len + 1));
    if (!full_path)
        return (NULL);
    i = 0;
    full_path[i++] = 'm';
    full_path[i++] = 'a';
    full_path[i++] = 'p';
    full_path[i++] = 's';
    full_path[i++] = '/';
    j = 0;
    while (map_name[j])
    {
        full_path[i++] = map_name[j++];
    }
    full_path[i] = '\0';
    return (full_path);
}

int find_map(int ac, char **argv)
{
    char *map_path;
    int fd;

    if (check_name(argv) && check_arg(ac))
    {
        map_path = create_map_path(argv[1]);
        if (!map_path)
        {
            printf("Error\nMap not found");
            return (-1);
        }
        fd = open(map_path, O_RDONLY);
        free(map_path);
        return (fd);
    }
    return (-1);
}

int extract_line(int fd)
{
    if (fd < 0)
}