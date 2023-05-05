/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:00:32 by mmarcott          #+#    #+#             */
/*   Updated: 2023/05/05 13:43:03 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	place_decor(t_tile *decs, t_game *valeur)
{
	void	*mlx;
	void	*win;
	t_tile	*current;

	current = decs;
	mlx = valeur->mlx;
	win = valeur->win;
	if (current->img)
		mlx_put_image_to_window(mlx, win, current->img, current->x, current->y);
	current = current->next;
	while (current)
	{
		mlx_put_image_to_window(mlx, win, current->img, current->x, current->y);
		if (current->next == NULL)
			return ;
		current = current->next;
	}
}

int	key_pressed(int keycode, t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	place_decor(game->decors, game);
	if (keycode == 2 || keycode == 124)
		ft_move_player(game, 100, 0);
	else if (keycode == 1 || keycode == 125)
		ft_move_player(game, 0, 100);
	else if (keycode == 0 || keycode == 123)
		ft_move_player(game, -100, 0);
	else if (keycode == 13 || keycode == 126)
		ft_move_player(game, 0, -100);
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	else
		mlx_put_image_to_window(game->mlx, game->win, game->player->img,
			game->player->x, game->player->y);
	return (1);
}

int	ft_quitt(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	ft_exit_free(game, "Qutting the game.");
	return (0);
}

int	ft_renderer(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	place_decor(game->decors, game);
	mlx_put_image_to_window(game->mlx, game->win, game->player->img,
		game->player->x, game->player->y);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*mapn;
	t_game	game;

	if (argc != 2 || !ft_check_name(argv[1]))
		ft_exit("You must provide the path of the map, use: ./so_long <map>",
			1);
	game.decors = ft_calloc(1, sizeof(t_tile));
	game.player = ft_calloc(1, sizeof(t_player));
	mapn = argv[1];
	game.moved = 0;
	ft_check_map_size(&game, open(mapn, O_RDONLY));
	ft_check_tiles(open(mapn, O_RDONLY), &game);
	ft_check_tiles_value(open(mapn, O_RDONLY), &game);
	game.title = "Le chien marin";
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.width, game.height, game.title);
	ft_init_map(&game, mapn);
	mlx_loop_hook(game.mlx, ft_renderer, &game);
	mlx_hook(game.win, 2, 0, key_pressed, &game);
	mlx_hook(game.win, 17, 0, ft_quitt, &game);
	mlx_loop(game.mlx);
	return (0);
}
