/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:55:12 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;

	result = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (result == 0)
		return (0);
	result = ft_memcpy(result, s, ft_strlen(s) + 1);
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strdup("Hello pisciners"));
	return 0;
}*/