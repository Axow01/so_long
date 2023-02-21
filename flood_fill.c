/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:20:30 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/21 13:53:34 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_flood_fill(char **map, int x, int y, int *c_count, int *e_count)
{
	if ((map[y][x] == '1' || map[y][x] == '2') || y < 0 || x < 0)
		return ;
	if (map[y][x] == 'C')
		*c_count = *c_count + 1;
	else if (map[y][x] == 'E')
		*e_count = *e_count + 1;
	map[y][x] = '2';
	ft_flood_fill(map, x, y - 1, c_count, e_count);
	ft_flood_fill(map, x, y + 1, c_count, e_count);
	ft_flood_fill(map, x - 1, y, c_count, e_count);
	ft_flood_fill(map, x + 1, y, c_count, e_count);
	return ;
}

void    ft_flood_init(char **map, t_game *game)
{
    int c_count;
    int e_count;

    c_count = 0;
    e_count = 0;
	ft_printf("before flood.. x: %d y: %d\n", game->player->x / 100, game->player->y / 100);
    ft_flood_fill(map, game->player->x / 100, game->player->y / 100, &c_count, &e_count);
	ft_printf("e_count: %d c_count: %d\n", e_count, c_count);
    if (c_count < 1 || e_count != 1)
        ft_exit("Flood fill error this map is not playable.", 1);
}