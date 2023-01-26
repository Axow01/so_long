/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 01:19:06 by mmarcott          #+#    #+#             */
/*   Updated: 2022/12/16 13:19:54 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*memory;
	size_t	i;

	i = 0;
	memory = malloc(nmemb * size);
	if (!memory)
		return (0);
	while (i < nmemb)
		memory[i++] = 0;
	return (memory);
}

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	joined = ft_calloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1),
			sizeof(char));
	if (!joined)
		return (NULL);
	while (s1 && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	return (s1 = ft_free(s1), s2 = ft_free(s2), joined);
}

void	*ft_free(char *p)
{
	if (p)
		free(p);
	return (NULL);
}

void	finalise(char **line, char **stash)
{
	int	i;
	int	k;

	put_line(line, *stash);
	k = ft_strlen(*line);
	i = 0;
	while (stash[0] && stash[0][k])
		stash[0][i++] = stash[0][k++];
	while (stash[0] && stash[0][i])
		stash[0][i++] = 0;
}
