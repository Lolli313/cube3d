/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:40:34 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_u(unsigned int n)
{
	char	buffer[13];
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		counter++;
	}
	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i > 0)
	{
		write(1, &buffer[--i], 1);
		counter++;
	}
	return (counter);
}
/*
int	main(void)
{
	ft_print_u(0);
	ft_print_c('\n');
	ft_print_u(42);
	ft_print_c('\n');
	ft_print_u(2147483647);	
	ft_print_c('\n');
	ft_print_u(4294967295);
	ft_print_c('\n');
	return (0);
}*/