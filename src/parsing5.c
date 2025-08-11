/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <njung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:17:39 by njung             #+#    #+#             */
/*   Updated: 2025/08/11 17:37:56 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int is_texture_element(char c)
{
    return (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'F' || c == 'C');
}

int is_map_element(char c)
{
    return (c == '1' || c == '0' || c == ' ');
}

int check_map_before_textures(int texture_count, char first_char)
{
    if (texture_count < 6 && is_map_element(first_char))
    {
        printf("Error\nMap found before all textures defined\n");
        return (0);
    }
    return (1);
}

int process_order_line(char *line, int *texture_count, int *map_started)
{
    if (line[0] == '\n' || line[0] == '\0')
        return (1);
    if (!*map_started && is_texture_element(line[0]))
    {
        (*texture_count)++;
        return (1);
    }
    if (!check_map_before_textures(*texture_count, line[0]))
        return (0);
    *map_started = 1;
    return (1);
}

