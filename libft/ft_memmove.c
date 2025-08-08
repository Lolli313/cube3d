/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:49:07 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*temp_dest;
	char	*temp_src;
	size_t	i;

	temp_dest = (char *)dest;
	temp_src = (char *)src;
	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	if (temp_dest > temp_src)
	{
		while (n-- > 0)
			temp_dest[n] = temp_src[n];
	}
	else
	{
		while (i++ < n)
			temp_dest[i - 1] = temp_src[i - 1];
	}
	return (dest);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	src[100] = "Hello pisciners!";

	printf("%s\n", (char *)ft_memmove(src, src + 6, 15));
	char	src1[100] = "Hello pisciners!";

	printf("%s\n", (char *)memmove(src1, src1 + 6, 15));
	return 0;
}*/