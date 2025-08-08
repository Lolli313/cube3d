/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:25:20 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	sub_len;

	if (s == 0)
		return (0);
	if (ft_strlen(s) < start)
		sub_len = 0;
	else if (ft_strlen(s) < start + len)
		sub_len = ft_strlen(s) - start;
	else
		sub_len = len;
	result = ft_calloc(sub_len + 1, sizeof(char));
	if (result == 0)
		return (0);
	ft_memcpy(result, s + start, sub_len);
	result[sub_len] = 0;
	return (result);
}
/*
int	main(void)
{
	printf("%s\n", ft_substr(NULL, 0, 12));
	return (0);
}*/