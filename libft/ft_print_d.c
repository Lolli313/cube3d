/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:17:12 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_d(int i)
{
	int	counter;

	counter = 0;
	ft_putnbr_fd(i, 1);
	if (i <= 0)
		counter++;
	while (i)
	{
		i /= 10;
		counter++;
	}
	return (counter);
}
/*
int	main(void)
{
	ft_print_d(0);
	ft_print_c('\n');
	ft_print_d(42);
	ft_print_c('\n');
	ft_print_d(-42);
	ft_print_c('\n');
	ft_print_d(2147483647);
	ft_print_c('\n');
	ft_print_d(-2147483648);
	ft_print_c('\n');
}*/