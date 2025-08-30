/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:36:46 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/30 18:16:06 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	add_door(t_cube *cube, int row, int col)
{
	t_door	*temp;
	t_door	*new_door;

	new_door = malloc(sizeof(t_door));
	if (!new_door)
		return ;
	new_door->door_x = col;
	new_door->door_y = row;
	new_door->is_open = false;
	new_door->next = NULL;
	if (cube->nbr_doors == 0)
	{
		cube->door = new_door;
		return ;
	}
	temp = cube->door;
	while (temp)
		temp = temp->next;
	temp = new_door;
}

t_door	*find_door(t_cube *cube)
{
	t_door	*temp;

	temp = cube->door;
	if (!temp)
		return (NULL);
	while (temp)
	{
		if (temp->door_x == cube->coord.map_x
			&& temp->door_y == cube->coord.map_y)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

bool	is_door_open(t_cube *cube)
{
	t_door	*temp;

	temp = find_door(cube);
	return (temp->is_open);
}

void	parse_door(t_cube *cube, int row, int col)
{
	cube->map.map[row][col] = 3;
	add_door(cube, row, col);
	cube->nbr_doors++;
}
