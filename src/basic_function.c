/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:41:06 by mmarcott          #+#    #+#             */
/*   Updated: 2023/05/05 13:39:57 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_init_sprites(t_game *game)
{
	int	x;
	int	y;

	game->sand = mlx_xpm_file_to_image(game->mlx, "sprites/sand.xpm", &x, &y);
	game->water = mlx_xpm_file_to_image(game->mlx, "sprites/water.xpm", &x, &y);
	game->chest = mlx_xpm_file_to_image(game->mlx, "sprites/chest.xpm", &x, &y);
	game->exit = mlx_xpm_file_to_image(game->mlx, "sprites/exit.xpm", &x, &y);
	game->playerimg = mlx_xpm_file_to_image(game->mlx, "sprites/character.xpm",
			&x, &y);
}

char	**ft_convert_map(int fd, t_game *game)
{
	char	**map;
	char	*line;
	int		row;
	int		col;

	row = 0;
	col = 0;
	map = (char **)ft_calloc(game->height / 100, sizeof(char *));
	while (col < game->height / 100)
		map[col++] = ft_calloc(game->width / 100, sizeof(char));
	col = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[++col] != '\n' && line[col])
			map[row][col] = line[col];
		col = -1;
		line = ft_free(line);
		row++;
	}
	close(fd);
	return (map);
}

void	ft_create_decors(t_tile **tiles, t_game *game, char **map)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	(void)tiles;
	ft_init_sprites(game);
	while (row < game->height / 100)
	{
		while (map[row][col])
		{
			ft_check_tile_type(game, col, row, map);
			col++;
		}
		col = 0;
		row++;
	}
}

void	ft_move_player(t_game *game, int modifierx, int modifiery)
{
	if (ft_check_moving_point(game, game->player->x + modifierx,
			game->player->y + modifiery))
		return ;
	game->player->x += modifierx;
	game->player->y += modifiery;
	game->moved += 1;
	ft_printf("Player moves: %d\n", game->moved);
}

void	ft_free_darray(char **array, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		array[y] = ft_free(array[y]);
		y++;
	}
	array = ft_free(array);
}
