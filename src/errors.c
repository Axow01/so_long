/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:22:00 by mick              #+#    #+#             */
/*   Updated: 2023/02/26 13:05:05 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void    ft_exit_free(t_game *game, char *string)
{
    t_tile *current;
    t_tile *follow;

    current = game->decors;
    while (current->next)
    {
        follow = current->next;
        free(current);
        current = follow;
    }
    game->player = ft_free(game->player);
    game = ft_free(game);
    //ft_printf("Freed sucessfully.\n");
    ft_exit(string, 0);
}
