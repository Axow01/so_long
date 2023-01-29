/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:04:00 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/29 15:21:16 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_map(char *map, t_decors **head, char therm, char type)
{
	char	*line;
	int		fd;
	int		i;
	void	*img;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	(void)map;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		while (line[i] && line[i] != '\n')
		{
			if (line[i] == therm || (therm == '0' && line[i] == 'C'))
			{
				add_decors(head, (*head)->img, x, y, type);
			}
			x += 100;
			i++;
		}
		i = 0;
		x = 0;
		y += 100;
		line = ft_free(line);
		line = get_next_line(fd);
	}
}

void ft_exit(char *message, int error)
{
	if (error)
		ft_printf("%s - Error!", message);
	else
		ft_printf("%s", message);	
	exit(error);
}
