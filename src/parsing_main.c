/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:09:15 by njung             #+#    #+#             */
/*   Updated: 2025/08/21 18:42:11 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_game(int ac, char **argv, t_cube *cube)
{
	if (!load_map(ac, argv, cube))
	{
		printf("Error: Failed to load map\n");
		return (0);
	}
	if (!validate_textures(&cube->map))
		return (0);
	if (!validate_map_content(cube))
		return (0);
	printf("Parsing completed successfully\n");
	return (1);
}
