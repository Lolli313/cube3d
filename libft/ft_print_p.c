/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:23:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptr_len(unsigned long long i)
{
	unsigned int	counter;

	counter = 0;
	while (i)
	{
		i /= 16;
		counter++;
	}
	return (counter);
}

void	ft_print_ptr(unsigned long long i, char *base)
{
	if (i >= 16)
	{
		ft_print_ptr(i / 16, base);
		ft_print_ptr(i % 16, base);
	}
	else
		write(1, &base[i], 1);
}

int	ft_print_p(unsigned long long i)
{
	if (i == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	ft_print_ptr(i, "0123456789abcdef");
	return (ft_ptr_len(i) + 2);
}
/*
int	main(void)
{
	char c = 't';
//	printf("%s\n", (char*)0);
//	ft_print_s(0);
//	printf("\n%p\n", (char*)0);
	ft_print_p(0);
	printf("\n%p\n", &c);
	ft_print_p(140726194326175);
}*/