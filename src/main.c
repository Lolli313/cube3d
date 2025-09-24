/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <njung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:00 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/24 14:32:58 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
	cos(θ - π/2) = sin(θ)
	sin(θ - π/2) = -cos(θ)
	cos(θ + π/2) = -sin(θ)
	sin(θ + π/2) = cos(θ)
*/

int	main(int ac, char **av)
{
	t_cube	cube;

	if (ac != 2)
		return (printf("Error\nWrong number of arguments\n"), 1);
	init_cube(&cube);
	init_image(&cube);
	if (!parse_game(ac, av, &cube))
		return (cleanup(&cube), 1);
	init_keys(&cube);
	init_hooks(&cube);
	render_image(&cube);
	mlx_loop(cube.mlx);
}
