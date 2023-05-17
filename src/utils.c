/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:46:50 by mmarcott          #+#    #+#             */
/*   Updated: 2023/05/17 13:36:14 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_count_tiles(int *player, int *exit, char line, t_game *game)
{
	if (line == 'P')
		*player += 1;
	else if (line == 'C')
		game->collected_c += 1;
	else if (line == 'E')
		*exit += 1;
}

void	ft_init_map(t_game *game, char *mapn)
{
	char	**map;

	if (!game->mlx || !game->win)
		ft_quitt(game);
	map = ft_convert_map(open(mapn, O_RDONLY), game);
	ft_create_decors(&game->decors, game, map);
	ft_flood_init(map, game);
	ft_free_darray(map, game->height / 100);
}

void	add_decors(t_game *game, int x, int y, char type)
{
	t_tile	*current;
	t_tile	*newbitch;

	current = game->decors;
	newbitch = ft_calloc(1, sizeof(t_tile));
	if (type == '1')
		newbitch->img = game->sand;
	else if (type == '0')
		newbitch->img = game->water;
	else if (type == 'E')
		newbitch->img = game->exit;
	else
		newbitch->img = game->chest;
	newbitch->x = x;
	newbitch->y = y;
	newbitch->type = type;
	newbitch->next = NULL;
	while (current->next)
		current = current->next;
	current->next = newbitch;
}
