/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:41:06 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/20 14:09:09 by mmarcott         ###   ########.fr       */
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

void	ft_playable(char **map, t_game **game)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row < (*game)->height / 100)
	{
		while (map[row][col])
		{
			if ((map[row][col] == 'C' || map[row][col] == 'E') && map[row][col
				+ 1] == '1' && map[row][col - 1] == '1' && map[row
				+ 1][col] == '1' && map[row - 1][col] == '1')
				ft_exit("The map is not playable. Come on !", 1);
			col++;
		}
		col = 0;
		row++;
	}
}

void	ft_create_decors(t_tile **tiles, t_game **game, char **map)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row < (*game)->height / 100)
	{
		while (map[row][col])
		{
			if (map[row][col] == '1')
				add_decors(tiles, mlx_xpm_file_to_image((*game)->mlx,
							"sprites/sand.xpm", &(*tiles)->x, &(*tiles)->y), col
						* 100, row * 100, '1');
			else if (map[row][col] == '0' || map[row][col] == 'P'
					|| map[row][col] == 'C')
				add_decors(tiles, mlx_xpm_file_to_image((*game)->mlx,
							"sprites/water.xpm", &(*tiles)->x, &(*tiles)->y),
						col * 100, row * 100, '0');
			if (map[row][col] == 'P')
			{
				(*game)->player->img = mlx_xpm_file_to_image((*game)->mlx,
						"sprites/character.xpm", &(*game)->player->x,
						&(*game)->player->y);
				(*game)->player->x = col * 100;
				(*game)->player->y = row * 100;
			}
			else if (map[row][col] == 'C')
				add_decors(tiles, mlx_xpm_file_to_image((*game)->mlx,
							"sprites/chest.xpm", &(*tiles)->x, &(*tiles)->y),
						col * 100, row * 100, 'C');
			col++;
		}
		col = 0;
		row++;
	}
}

void	ft_move_player(t_player **player, int modifierx, int modifiery)
{
	(*player)->x += modifierx;
	(*player)->y += modifiery;
}

void	ft_exit(char *message, int error)
{
	if (error)
		ft_printf("Error\n%s\n", message);
	else
		ft_printf("%s", message);
	exit(error);
}