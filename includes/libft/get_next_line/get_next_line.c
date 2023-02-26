/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 01:16:49 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/16 11:05:50 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_the_file(int fd, char **buffer, ssize_t *bytes)
{
	*buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	*bytes = read(fd, *buffer, BUFFER_SIZE);
	return (1);
}

static int	analyse(char *stash)
{
	int	i;

	i = 0;
	while (stash[i])
	{
		if (stash[i++] == '\n')
			return (1);
	}
	return (0);
}

void	put_line(char **line, char *stash)
{
	int	i;

	i = 0;
	*line = ft_calloc((ft_strlen(stash) + 1), sizeof(char));
	while (stash[i] && stash[i] != '\n')
	{
		line[0][i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[0][i++] = '\n';
}

int	ft_find(char *stash, ssize_t bytes)
{
	int	i;

	i = 0;
	while (stash && stash[i])
	{
		if (stash[i] == 0 || stash[i] == '\n')
			return (1);
		i++;
	}
	if ((bytes == 0 || bytes < BUFFER_SIZE) && i > 0)
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (stash = ft_free(stash), NULL);
	bytes = BUFFER_SIZE;
	while (bytes >= BUFFER_SIZE)
	{
		read_the_file(fd, &buffer, &bytes);
		stash = ft_strjoin(stash, buffer);
		if (!stash || bytes < 0 || (bytes <= 0 && !ft_find(stash, bytes)))
			return (stash = ft_free(stash), NULL);
		if (analyse(stash) && ft_strlen(stash) > 0)
			return (finalise(&line, &stash), line);
	}
	if (ft_find(stash, bytes) || bytes < BUFFER_SIZE)
		return (finalise(&line, &stash), stash = ft_free(stash), line);
	return (stash = ft_free(stash), NULL);
}
