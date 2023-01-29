/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_other_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:04:00 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/29 17:44:07 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_create_map(char *map, t_tile **head, char therm, char type)
{
	char	*line;
	int		fd;
	int		i;
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
	line = ft_free(line);
}

int	ft_check_name(void)
{
	
	return (1);
}

int	ft_check_map(char *map, t_game **game)
{
	char	*line;
	int		collectible;
	int		player_spawn;
	int		exit;
	int		i;

	collectible = 0;
	player_spawn = 0;
	exit = 0;
	line = get_next_line(open(map, O_RDONLY));
	if (ft_strlen(line) * 100 > 2500)
		ft_exit("The map is too big for my little system :(\n", 1);
	(*game)->width = ft_strlen(line) * 100;
	return (1);
}

void	ft_exit(char *message, int error)
{
	if (error)
		ft_printf("%s - Error!", message);
	else
		ft_printf("%s", message);
	exit(error);
}
