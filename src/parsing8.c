/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:48:33 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/30 18:53:40 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	assign_max_width(char *line, int *max_width)
{
	int	current_width;

	current_width = 0;
	current_width = ft_strlen(line);
	if (line[current_width - 1] == '\n')
		current_width--;
	if (current_width > *max_width)
		*max_width = current_width;
}
