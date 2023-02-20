/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:41:06 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/20 10:45:13 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_convert_map(int fd, t_game **game)
{
	char	**map;
	char	*line;
	int		row;
	int		col;

	row = 0;
	col = 0;
	map = (char **)ft_calloc((*game)->height / 100, sizeof(char *));
	while (col < (*game)->height / 100)
		map[col++] = ft_calloc((*game)->width / 100, sizeof(char));
	col = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[col] != '\n' && line[col])
        {
			map[row][col] = line[col];
            col++;
        }
		map[row][col] = 0;
		col = 0;
		line = ft_free(line);
		row++;
	}
	return (map);
}

void	ft_exit(char *message, int error)
{
	if (error)
		ft_printf("Error\n%s\n", message);
	else
		ft_printf("%s", message);
	exit(error);
}