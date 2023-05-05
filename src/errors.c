/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:22:00 by mick              #+#    #+#             */
/*   Updated: 2023/05/05 13:45:15 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_exit_free(t_game *game, char *string)
{
	t_tile	*current;
	t_tile	*follow;

	current = game->decors;
	while (current->next)
	{
		follow = current->next;
		free(current);
		current = follow;
	}
	game->player = ft_free(game->player);
	ft_exit(string, 0);
}

void	ft_exit(char *message, int error)
{
	if (error)
		ft_printf("Error\n%s\n", message);
	else
		ft_printf("%s", message);
	exit(error);
}
