/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:49:19 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*new_string(const char *s1, size_t start, size_t len)
{
	char	*result;
	size_t	i;

	if (len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	result = ft_calloc(len + 1, sizeof(char));
	if (result == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		result[i] = s1[start + i];
		i++;
	}
	return (result);
}

static size_t	match_char(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (s1 == 0)
		return (0);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (match_char(s1[i], set))
		i++;
	while (match_char(s1[j], set))
		j--;
	return (new_string(s1, i, j - (i - 1)));
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strtrim("Hello beautiful pisciners", "abcde"));
	return(0);
}*/