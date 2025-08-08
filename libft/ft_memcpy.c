/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:12:04 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*temp_dest;
	const char	*temp_src;

	if (dest == 0 && src == 0)
		return (0);
	temp_dest = dest;
	temp_src = src;
	while (n > 0)
	{
		*temp_dest = *temp_src;
		temp_dest++;
		temp_src++;
		n--;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
//	char	src[] = "\0";
//	char	dest[] = "\0";

//	printf("%s\n", (char *)memcpy(0, 0, 3));
//	char	src1[] = "\0";
//	char	dest1[] = "\0";

	printf("%s\n", (char *)ft_memcpy(0, "Hello pisciners", 3));
	return 0;
}*/