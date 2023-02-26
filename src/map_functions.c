/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:04:00 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/26 13:05:15 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_check_name(char *map)
{
	char	*s;

	s = ft_strrchr(map, '.');
	if (!s || ft_strncmp(s, ".ber", ft_strlen(s) + 1) != 0)
		ft_exit("Come on this is not a valid map file extension?", 1);
	return (1);
}

int	ft_check_map_size(char *map, t_game **game)
{
	char	*line;
	int		i;
	int		length_line;
	int		height;

	height = 1;
	i = open(map, O_RDONLY);
	ft_check_name(map);
	line = get_next_line(i);
	length_line = ft_strlen(line);
	free(line);
	while (1)
	{
		line = get_next_line(i);
		if (!line)
			break ;
		if (ft_strlen(line) != length_line)
			ft_exit("Map error: the lines are not equal in length\n", 1);
		height++;
		free(line);
	}
	(*game)->width = (length_line - 1) * 100;
	(*game)->height = height * 100;
	close(i);
	if ((*game)->height > 1300 || (*game)->width > 2500)
		ft_exit("Map error: width or height to big.", 1);
	return (1);
}

void	ft_check_tiles(int fd, t_game **game)
{
	char	*line;
	int		height;
	int		width;

	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (height == 0 || height == ((*game)->height / 100) - 1)
		{
			if (!ft_check_line(line, '1', 1))
				ft_exit("Map error: first and last line wrong.", 1);
		}
		else
		{
			if (!ft_check_line(line, '1', 0))
				ft_exit("Map error: the sides of the map are wrong.", 1);
		}
		close(fd);
		line = ft_free(line);
		height++;
	}
}

int	ft_check_line(char *line, char check, int all)
{
	int	i;

	i = 0;
	if (all)
	{
		while (line[i] != '\n' && line[i])
		{
			if (line[i] != check && line[i] != '\n')
				return (0);
			i++;
		}
	}
	else
	{
		if (line[0] != check || line[ft_strlen(line) - 2] != check)
			return (0);
	}
	return (1);
}

void	ft_check_tiles_value(int fd, t_game *game)
{
	int		player;
	int		exit;
	int		i;
	char	*line;

	game->collected_c = 0;
	player = 0;
	exit = 0;
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[i])
		{
			if (line[i] == 'P')
				player += 1;
			else if (line[i] == 'C')
				game->collected_c += 1;
			else if (line[i] == 'E')
				exit += 1;
			i++;
		}
		i = 0;
		line = ft_free(line);
	}
	close(fd);
	if (exit != 1 || game->collected_c < 1 || player != 1)
		ft_exit("Map error: to much player, exits or not enough collectibles.",
				1);
}
