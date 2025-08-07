/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:26:20 by njung             #+#    #+#             */
/*   Updated: 2024/12/17 13:49:09 by njung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_storage(char *storage)
{
	char	*new_storage;
	size_t	i;
	size_t	j;

	i = 0;
	while (storage[i] != '\n' && storage[i])
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	new_storage = (char *) malloc((ft_strlen(storage) - i + 1) * sizeof(char));
	if (!new_storage)
		return (NULL);
	i++;
	j = 0;
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free(storage);
	return (new_storage);
}

char	*extract_line(char *storage)
{
	char	*line;
	int		i;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] != '\n' && storage[i])
		i++;
	line = (char *) malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] != '\n' && storage[i])
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		line[i] = storage[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*file_read(int fd, char *storage)
{
	ssize_t	bytes_read;
	char	*buff;

	buff = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(storage, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			free(storage);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		storage = ft_strjoin(storage, buff);
	}
	free(buff);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char		*buff_storage;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff_storage = file_read(fd, buff_storage);
	if (!buff_storage)
		return (NULL);
	line = extract_line(buff_storage);
	buff_storage = update_storage(buff_storage);
	return (line);
}
