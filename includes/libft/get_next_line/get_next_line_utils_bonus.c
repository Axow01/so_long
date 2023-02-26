/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 01:19:06 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/28 20:18:31 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoingnl(char *s1, char *s2)
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
