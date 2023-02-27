/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:46:50 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/27 11:05:53 by mmarcott         ###   ########.fr       */
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

	map = ft_convert_map(open(mapn, O_RDONLY), &game);
	ft_create_decors(&game->decors, &game, map);
	ft_flood_init(map, game);
	ft_free_darray(map, game->height / 100);
}
