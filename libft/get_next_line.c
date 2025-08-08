/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:52:59 by aakerblo          #+#    #+#             */
/*   Updated: 2025/01/16 17:48:17 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*str;

	i = ft_strlen(s);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}*/

int	read_buffer(int fd, char **stash, char *buffer)
{
	char	*temp;
	int		rd;

	ft_bzero(buffer, GNL_BUFFER_SIZE + 1);
	rd = read(fd, buffer, GNL_BUFFER_SIZE);
	if (rd < 0)
	{
		free (*stash);
		*stash = NULL;
		return (-1);
	}
	if (rd == 0)
		return (0);
	temp = ft_strjoin(*stash, buffer);
	if (temp == NULL)
	{
		free (*stash);
		*stash = NULL;
		return (-1);
	}
	free(*stash);
	*stash = NULL;
	*stash = temp;
	return (rd);
}

void	get_result(char **stash, char **result)
{
	char	*c;
	size_t	len;
	size_t	i;

	c = ft_strchr(*stash, '\n');
	if (c == 0)
		len = ft_strlen(*stash) + 1;
	else
		len = c - *stash + 2;
	*result = (char *)malloc(len * sizeof(char));
	if (!result)
		return ;
	i = 0;
	while (i < len - 1)
	{
		(*result)[i] = (*stash)[i];
		i++;
	}
	(*result)[i] = '\0';
}

void	remove_result(char **stash)
{
	char	*c;
	char	*temp;

	c = ft_strchr(*stash, '\n');
	if (c == 0)
	{
		free (*stash);
		*stash = NULL;
		return ;
	}
	temp = ft_strdup(c + 1);
	if (temp == 0)
	{
		free (*stash);
		*stash = NULL;
		return ;
	}
	free(*stash);
	*stash = NULL;
	*stash = temp;
}

char	*get_next_line(int fd)
{
	static char	*stash[GNL_MAX_FD];
	char		*buffer;
	int			rd;
	char		*line;

	if (fd < 0 || GNL_BUFFER_SIZE <= 0 || fd > GNL_MAX_FD)
		return (gnl_free_stash(&stash[fd]), NULL);
	buffer = (char *)malloc((GNL_BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	if (stash[fd] == NULL)
		stash[fd] = ft_strdup("\0");
	rd = 1;
	while (rd > 0 && ft_strchr(stash[fd], '\n') == NULL)
		rd = read_buffer(fd, &stash[fd], buffer);
	free (buffer);
	if (rd == -1 || ft_strlen(stash[fd]) == 0)
		return (gnl_free_stash(&stash[fd]), NULL);
	get_result(&stash[fd], &line);
	remove_result(&stash[fd]);
	return (line);
}
