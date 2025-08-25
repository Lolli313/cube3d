/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:18:53 by njung             #+#    #+#             */
/*   Updated: 2025/08/25 17:10:38 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int check_xpm_extension(char *texture)
{
    size_t len;
    
    len = ft_strlen(texture);
    if (len < 4)
    {
		printf("Error: Wrong texture extension\n");
        return (0);
    }
    if (texture[len - 4] == '.' && texture[len - 3] == 'x' && 
        texture[len - 2] == 'p' && texture[len - 1] == 'm')
        return (1);
    printf("Error: Wrong texture extension\n");
    return (0);
}

int check_texture_file(char *path)
{
    int fd;
    
    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: While loading textures\n");
        return (0);
    }
    close(fd);
    return (1);
}

int validate_textures(t_map *map)
{
    if (!map->NO || !map->SO || !map->WE || !map->EA)
    {
        printf("Error: Missing texture(s)\n");
        return (0);
    }
    if (map->floor == -1 || map->ceiling == -1)
    {
        printf("Error: Missing floor or ceiling color\n");
        return (0);
    }
    return (1);
}

int validate_map_content(t_cube *cube)
{
    int player_count;
    int i;
    int j;

    player_count = 0;
    i = 0;
    while (i < MAP_Y)
    {
        j = 0;
        while (j < MAP_X)
        {
//			printf("%d, ", cube->map.map[i][j]);
            if (cube->map.map[i][j] == 2)
                player_count++;
            j++;
        }
//		printf("\n");
        i++;
    }
//	printf("player count is %d\n", player_count);
    if (player_count != 1)
    {
        printf("Error: Map must have exactly one player\n");
        return (0);
    }
    return (1);
}

int validate_element_order(int fd)
{
    char *line;
    int texture_count;
    int map_started;
    int result;

    texture_count = 0;
    map_started = 0;
    while ((line = get_next_line(fd)))
    {
        result = process_order_line(line, &texture_count, &map_started);
        free(line);
        if (!result)
            return (0);
    }
    return (1);
}
