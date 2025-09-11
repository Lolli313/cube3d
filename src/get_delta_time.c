/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delta_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:06:36 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/11 15:10:24 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	get_delta_time(void)
{
	static struct timeval	last;
	struct timeval			now;
	double					delta;

	gettimeofday(&now, NULL);
	if (last.tv_sec == 0)
		last = now;
	delta = (now.tv_sec - last.tv_sec) + (now.tv_usec - last.tv_usec) / 1e6;
	last = now;
	return (delta);
}
