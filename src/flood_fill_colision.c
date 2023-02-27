/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_colision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:20:30 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/27 10:54:00 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_flood_fill(char **map, int x, int y, t_game *game)
{
	if ((map[y][x] == '1' || map[y][x] == '2') || y < 0 || x < 0)
		return ;
	if (map[y][x] == 'C')
		game->c_count += 1;
	else if (map[y][x] == 'E')
		game->e_count += 1;
	map[y][x] = '2';
	ft_flood_fill(map, x, y - 1, game);
	ft_flood_fill(map, x, y + 1, game);
	ft_flood_fill(map, x - 1, y, game);
	ft_flood_fill(map, x + 1, y, game);
	return ;
}

void	ft_flood_init(char **map, t_game *game)
{
	game->c_count = 0;
	game->e_count = 0;
	ft_flood_fill(map, game->player->x / 100, game->player->y / 100, game);
	if (game->c_count < 1 || game->e_count != 1)
		ft_exit("Flood fill error this map is not playable.", 1);
}

int	ft_check_moving_point(t_game **game, int x, int y)
{
	t_tile	*current;

	current = (*game)->decors;
	while (current->next)
	{
		if (current->x == x && current->y == y && (current->type == '1'
				|| current->type == 'C' || (current->type == 'E'
					&& (*game)->collected_c == 0)))
		{
			if (current->type == 'C')
			{
				(*game)->collected_c--;
				ft_delete_tile((*game)->decors, x, y, 'C');
				return (0);
			}
			else if (current->type == 'E' && (*game)->collected_c == 0)
				ft_exit_free(*game, "GG, you won the game. Nice work !");
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	ft_delete_tile(t_tile *tile, int x, int y, char type)
{
	t_tile	*current;
	t_tile	*last;

	last = tile;
	current = tile->next;
	while (current->next || last->next)
	{
		if (current->x == x && current->y == y && current->type == type)
		{
			last->next = current->next;
			free(current);
			return ;
		}
		last = last->next;
		current = current->next;
	}
}

void	ft_check_tile_type(t_game *game, int col, int row, char **map)
{
	if (map[row][col] == '1')
		add_decors(game, col * 100, row * 100, '1');
	else if (map[row][col] == '0' || map[row][col] == 'P'
			|| map[row][col] == 'C')
		add_decors(game, col * 100, row * 100, '0');
	if (map[row][col] == 'P')
	{
		game->player->img = game->playerimg;
		game->player->x = col * 100;
		game->player->y = row * 100;
	}
	else if (map[row][col] == 'C')
		add_decors(game, col * 100, row * 100, 'C');
	else if (map[row][col] == 'E')
		add_decors(game, col * 100, row * 100, 'E');
}
