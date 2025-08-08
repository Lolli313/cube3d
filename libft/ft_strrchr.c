/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:43:10 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	char	i;

	temp = NULL;
	i = (char)c;
	while (*s)
	{
		if (*s == i)
			temp = (char *)s;
		s++;
	}
	if (i == 0)
		return (((char *)s));
	return (temp);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strrchr("Hello pisciners", ' '));
	return (0);
}*/