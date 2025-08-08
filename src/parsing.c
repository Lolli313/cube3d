/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <njung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:43:59 by njung             #+#    #+#             */
/*   Updated: 2025/08/08 18:26:52 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int check_name(char **argv)
{
    int len;

    len = 0;
    if (!argv || !argv[1])
        printf("Error\nWrong file name");
    while (argv[1][len])
        len++;
    if (len < 5)
        printf("Error\nWrong file name");
    if (argv[1][len - 4] == '.' && 
        argv[1][len - 3] == 'c' && 
        argv[1][len - 2] == 'u' && 
        argv[1][len - 1] == 'b')
        return (1);
    printf("Error\nWrong file name");
    return (0);
}
int check_arg(int ac)
{
    if (ac != 2)
    {
        printf("Error\nChoose a map");
        return (0);
    }
    return (1);
}

int parse_rgb(char *line)
{
    char **rgb_values;
    int r;
    int g;
    int b;
    int color;

    rgb_values = ft_split(line, ',');
    if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
        return (-1);
    r = ft_atoi(rgb_values[0]);
    g = ft_atoi(rgb_values[1]);
    b = ft_atoi(rgb_values[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (-1);
    color = (r << 16) | (g << 8) | b; // to create the real vlaue
    ft_free_matrix(rgb_values); // nice find
    return (color);
}

int parse_texture_line(char *line, t_map *map)
{
    if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
    {
        map->NO = load_textures(NULL, line + 3);
        return (1);
    }
    else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
    {
        map->SO = load_textures(NULL, line + 3);
        return (1);
    }
    else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
    {
        map->WE = load_textures(NULL, line + 3);
        return (1);
    }
    else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
    {
        map->EA = load_textures(NULL, line + 3);
        return (1);
    }
    else if (line[0] == 'F' && line[1] == ' ')
    {
        map->floor = parse_rgb(line + 2);
        return (map->floor != -1);
    }
    else if (line[0] == 'C' && line[1] == ' ')
    {
        map->ground = parse_rgb(line + 2);
        return (map->ground != -1);
    }
    return (0);
}

int parse_map_file(int fd, t_cube *cube)
{
    char *line;
    int textures_done;
    int map_row;
    int texture_count;

    textures_done = 0;
    map_row = 0;
    texture_count = 0;
    while ((line = get_next_line(fd)))
    {
        if (line[0] == '\n' || line[0] == '\0')
        {
            free(line);
            continue;
        }
        if (!textures_done && parse_texture_line(line, &cube->map))
        {
            texture_count++;
            free(line);
            continue;
        }
        if (!textures_done)
        {
            if (texture_count < 6)
            {
                printf("Error\nInvalid map format");
                free(line);
                return (0);
            }
            textures_done = 1;
        }
        if (textures_done && map_row < MAP_Y)
        {
            parse_map_line(line, cube, map_row);
            map_row++;
        }
        free(line);
    }
    return (1);
}

int parse_map_line(char *line, t_cube *cube, int row)
{
    int col;
    int i;

    col = 0;
    i = 0;
    while (line[i] && col < MAP_X)
    {
        if (line[i] == '1')
            cube->map.map[col][row] = 1;
        else if (line[i] == '0')
            cube->map.map[col][row] = 0;
        else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        {
            cube->map.map[col][row] = 0;
            cube->p.position_x = col;
            cube->p.position_y = row;
            set_player_direction(cube, line[i]);
        }
        else if (line[i] == ' ')
            cube->map.map[col][row] = 1;
        if (line[i] != ' ' || (line[i] == ' ' && col > 0))
            col++;
        i++;
    }
    return (1);
}
void set_player_direction(t_cube *cube, char direction)
{
    if (direction == 'N')
        cube->p.player_direction = 3 * PI / 2; // 270 degrees ( north)
    else if (direction == 'S')
        cube->p.player_direction = PI / 2; // 90 degrees ( south )
    else if (direction == 'E')
        cube->p.player_direction = 0; // 0 ( right )
    else if (direction == 'W')
        cube->p.player_direction = PI; // 180 ( left )
}
