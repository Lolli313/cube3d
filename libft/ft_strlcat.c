/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:54:05 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	lenght;
	size_t	d_len;
	size_t	s_len;

	if (dest == 0 && size == 0)
		return (0);
	s_len = ft_strlen(src);
	d_len = ft_strlen(dest);
	lenght = s_len + d_len;
	if (size <= d_len)
	{
		d_len = size;
		return (d_len + s_len);
	}
	if (lenght < size)
		ft_memcpy((dest + ft_strlen(dest)), src, (ft_strlen(src) + 1));
	else
	{
		ft_memcpy((dest + ft_strlen(dest)), src, (size - ft_strlen(dest)));
		dest[size - 1] = 0;
	}
	return (lenght);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	char	src[] = "pisciners!";
	char	dest[20] = "ha";

	printf("%lu\n", strlcat(dest, src, 30));
	printf("%s\n", dest);
	char	src1[] = "pisciners!";
	char	dest1[20] = "ha";
//	NEED TO ADD "-lbsd" TO THE COMPILER FOR SOME REASON!!!
	printf("%lu\n", ft_strlcat(0, src1, 0));
	printf("%s\n", dest1);
	return 0;
}*/