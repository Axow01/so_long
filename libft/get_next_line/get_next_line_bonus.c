/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 01:16:49 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/28 20:17:54 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	read_the_file(int fd, char **buffer, ssize_t *bytes)
{
	*buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer[0])
	{
		*buffer = NULL;
		return (0);
	}
	*bytes = read(fd, *buffer, BUFFER_SIZE);
	return (1);
}

void	put_line(char **line, char *stash)
{
	int	i;

	i = 0;
	*line = ft_calloc((ft_strlen(stash) + 1), sizeof(char));
	if (!line[0])
	{
		*line = NULL;
		return ;
	}
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
	static char	*stash[OPEN_MAX];
	char		*line;
	char		*buffer;
	ssize_t		bytes;
	int			size_of_stash;

	buffer = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
		return (stash[fd] = ft_free(stash[fd]), NULL);
	bytes = BUFFER_SIZE;
	while (bytes >= BUFFER_SIZE)
	{
		read_the_file(fd, &buffer, &bytes);
		stash[fd] = ft_strjoingnl(stash[fd], buffer);
		size_of_stash = ft_strlen(stash[fd]);
		if (!stash[fd] || bytes < 0 || (bytes <= 0 && !ft_find(stash[fd],
					bytes)))
			return (stash[fd] = ft_free(stash[fd]), NULL);
		if (ft_find(stash[fd], bytes) && size_of_stash > 0)
			return (finalise(&line, &stash[fd]), line);
	}
	if (ft_find(stash[fd], bytes) || bytes < BUFFER_SIZE)
		return (finalise(&line, &stash[fd]), stash[fd] = ft_free(stash[fd]),
			line);
	return (stash[fd] = ft_free(stash[fd]), NULL);
}
