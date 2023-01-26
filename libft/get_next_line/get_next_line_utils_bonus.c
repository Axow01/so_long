/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 01:19:06 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/26 16:08:12 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
