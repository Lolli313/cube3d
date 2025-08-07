/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <njung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:43:59 by njung             #+#    #+#             */
/*   Updated: 2025/08/07 14:51:29 by njung            ###   ########.fr       */
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
    if (len >= 4 && 
        argv[1][len - 4] == '.' && 
        argv[1][len - 3] == 'b' && 
        argv[1][len - 2] == 'e' && 
        argv[1][len - 1] == 'r')
        return (1);
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
