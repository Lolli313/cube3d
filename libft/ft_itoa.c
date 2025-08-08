/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:06:09 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lengthcheck(int n)
{
	int	result;

	result = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
		result++;
	while (n)
	{
		n /= 10;
		result++;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int		length;
	char	*result;

	length = lengthcheck(n);
	result = ft_calloc(length + 1, sizeof(char));
	if (!result)
		return (0);
	if (n == -2147483648)
	{
		result[--length] = '8';
		n /= 10;
	}
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	else if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[length-- - 1] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	char *ptr = ft_itoa(-2147483648);
	printf("%s\n", ptr);
	free(ptr);
	return(0);
}*/