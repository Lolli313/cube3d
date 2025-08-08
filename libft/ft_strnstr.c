/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:35:37 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	big_len;

	i = 0;
	j = 0;
	if (big == 0 && len == 0)
		return (0);
	big_len = ft_strlen(big);
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (i < len && i < big_len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && i + j < len)
		{
			j++;
			if (little[j] == 0)
				return ((char *)big + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
/*
#include <bsd/string.h>
int	main(void)
{
//	printf("%s\n", strnstr("", "aabc", 13));
	printf("%s\n", ft_strnstr("aabc", "aabc", 13));
	return (0);
}*/