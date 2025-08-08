/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:36:13 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	counter;
	int	i;
	int	s_len;

	counter = 0;
	i = 0;
	s_len = ft_strlen(s);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
			counter++;
		while (s[i] != c && i < s_len)
			i++;
	}
	return (counter);
}

static char	*word_dup(char const *s, char c)
{
	char	*word;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (s[j] && s[j] != c)
		j++;
	word = ft_calloc(j + 1, sizeof(char));
	if (word == 0)
		return (0);
	while (i < j)
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

static void	give_value(int *n, int *i)
{
	*n = 1;
	*i = 0;
}

static void	*ft_free(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		n;
	char	**result;
	int		i;

	if (s == 0)
		return (0);
	result = ft_calloc(word_count(s, c) + 1, sizeof(char *));
	if (word_count(s, c) == 0)
		return (result);
	if (result == 0)
		return (0);
	give_value(&n, &i);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			result[n - 1] = word_dup(&s[i], c);
		if (result[n - 1] == 0)
			return (ft_free(result));
		if (n++ == word_count(s, c))
			return (result);
		i += ft_strlen(result[n - 2]);
	}
	return (result);
}
/*
int	main(void)
{
	char	**arr;
	char	str[] = "hello";
	char	c = ':';
	int		m = word_count(str, c);

	arr = ft_split(str, c);
	for (int i = 0; arr[i]; i++)
		printf("%s\n", arr[i]);
	for (int j = 0; j < m; j++)
		free(arr[j]);
	free(arr);
	return (0);
}*/
