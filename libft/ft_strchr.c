/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:42:15 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	i;

	i = (char)c;
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (i == 0)
		return (((char *)s));
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strchr("Hello pisciners", 'A'));
	printf("%s\n", strchr("Hello pisciners", 'A'));
	return 0;
}*/