/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:08 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	lenght;

	lenght = ft_strlen(src);
	if (lenght < size)
		ft_memcpy(dest, src, lenght + 1);
	else if (size != 0)
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = 0;
	}
	return (lenght);
}
/*
#include <bsd/string.h>
#include <stdio.h>
int	main(void)
{
	char	src[] = "Hello pisciners!";
	char	dest[14];

	printf("%zu\n", ft_strlcpy(dest, src, 17));
	printf("%s\n", dest);
	char	src1[] = "Hello pisciners!";
	char	dest1[14];
//	NEED TO ADD "-lbsd" TO THE COMPILER FOR SOME REASON!!!
	printf("%zu\n", strlcpy(dest1, src1, 17));
	printf("%s\n", dest);
	return 0;
}*/