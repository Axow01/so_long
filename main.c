/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:00:32 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/25 15:14:51 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	int	modifier;

	modifier = 100;
	mlx_clear_window(game->mlx, game->win);
	place_decor(game->decors, game);
	if (keycode == 2 || keycode == 124) // d
		ft_move_player(&game, 100, 0);
	else if (keycode == 1 || keycode == 125) // s
		ft_move_player(&game, 0, 100);
	else if (keycode == 0 || keycode == 123) // a
		ft_move_player(&game, -100, 0);
	else if (keycode == 13 || keycode == 126)
		ft_move_player(&game, 0, -100);
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	else
		mlx_put_image_to_window(game->mlx, game->win, game->player->img,
				game->player->x, game->player->y);
	return (0);
}

void	add_decors(t_tile **head, void *img, int x, int y, char type)
{
	t_tile	*current;
	t_tile	*newbitch;

	current = *head;
	newbitch = ft_calloc(1, sizeof(t_tile));
	newbitch->img = img;
	newbitch->x = x;
	newbitch->y = y;
	newbitch->type = type;
	newbitch->next = NULL;
	while (current->next)
		current = current->next;
	current->next = newbitch;
}

int	ft_renderer(t_game **game)
{
	place_decor((*game)->decors, *game);
	mlx_put_image_to_window((*game)->mlx, (*game)->win, (*game)->player->img,
			(*game)->player->x, (*game)->player->y);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*mapn;
	t_game	*game;
	char	**map;
	int		y;

	if (argc != 2)
		ft_exit("You must provide the path of the map, use: ./so_long <map>",
				1);
	ft_printf("PID: %d\n", getpid());
	game = ft_calloc(1, sizeof(t_game));
	game->decors = ft_calloc(1, sizeof(t_tile));
	game->player = ft_calloc(1, sizeof(t_player));
	mapn = argv[1];
	ft_check_map_size(mapn, &game);
	ft_check_tiles(open(mapn, O_RDONLY), &game);
	ft_check_tiles_value(open(mapn, O_RDONLY), game);
	map = ft_convert_map(open(mapn, O_RDONLY), &game);
	game->title = "Le chien marin";
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height,
			game->title);
	ft_create_decors(&game->decors, &game, map);
	ft_flood_init(map, game);
	// Free game->map here and close fd.
	y = 0;
	while (y < game->height / 100)
	{
		//free(map[y]);
		y++;
	}
	//map = ft_free(map);
	//ft_free_darray(map, game->height / 100);
	mlx_loop_hook(game->mlx, ft_renderer, &game);
	mlx_hook(game->win, 2, 0, key_pressed, game);
	mlx_loop(game->mlx);
	return (0);
}
