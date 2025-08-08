/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:54:54 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hex_len(unsigned int i)
{
	int	counter;

	counter = 0;
	if (i == 0)
		counter++;
	while (i)
	{
		i /= 16;
		counter++;
	}
	return (counter);
}

void	ft_puthexnbr(unsigned int n, char *base)
{
	if (n >= 16)
	{
		ft_puthexnbr(n / 16, base);
		ft_puthexnbr(n % 16, base);
	}
	else
		write(1, &base[n], 1);
}

int	ft_print_x(unsigned int n, char c)
{
	if (c == 'x')
		ft_puthexnbr(n, "0123456789abcdef");
	else
		ft_puthexnbr(n, "0123456789ABCDEF");
	return (ft_hex_len(n));
}
/*
int	main(void)
{
	printf("%x\n", -1);
	ft_print_x(-1, 'x');
	printf("\n%x\n", 0);
	ft_print_x(0, 'X');
	printf("\n%x\n", 42);
	ft_print_x(42, 'X');
	printf("\n%x\n", 2147483647);
	ft_print_x(2147483647, 'X');
	printf("\n%lx\n", 4294967295);
	ft_print_x(4294967295, 'x');
}*/