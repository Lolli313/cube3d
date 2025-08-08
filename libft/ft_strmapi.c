/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:22:12 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*result;

	if (s == 0)
		return (0);
	i = 0;
	result = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!result)
		return (0);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}
/*
char	makeupper(unsigned int index, char c)
{
	(void)index;
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

int	main(void)
{
	char	*s = "Hello pisciners!";
	printf("%s\n", ft_strmapi(s, makeupper));
	return (0);
}*/