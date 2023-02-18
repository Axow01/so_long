/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:00:32 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/18 14:11:40 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(char *message)
{
	ft_printf("Error: %s\n", message);
}

void	place_decor(t_tile *decs, t_game *valeur)
{
	void	*mlx;
	void	*win;
	t_tile	*current;

	current = decs;
	mlx = valeur->mlx;
	win = valeur->win;
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

int	check_list(t_tile *head, int x, int y)
{
	t_tile	*current;

	current = head;
	while (current->next)
	{
		if ((current->type == 's') && x == current->x && y == current->y)
			return (1);
		current = current->next;
	}
	return (0);
}

void	move_player(t_game *game, int xmodifier, int ymodifier)
{
	if (!check_list(game->decors, game->player->x + xmodifier, game->player->y
			+ ymodifier))
	{
		mlx_put_image_to_window(game->mlx, game->win, game->player->img,
				game->player->x += xmodifier, game->player->y += ymodifier);
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->win, game->player->img,
				game->player->x, game->player->y);
	}
}

int	key_pressed(int keycode, t_game *game)
{
	int	modifier;

	modifier = 100;
	mlx_clear_window(game->mlx, game->win);
	//place_decor(game->decors, game);
	if (keycode == 2) // d
		move_player(game, 100, 0);
	else if (keycode == 1) // s
		move_player(game, 0, 100);
	else if (keycode == 0) // a
		move_player(game, -100, 0);
	else if (keycode == 13)
		move_player(game, 0, -100);
	else if (keycode == 53)
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
	t_tile	*newbitch;
	t_tile	*current;

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

void	add_end_list(t_tile **head, t_tile *ajout)
{
	t_tile	*current;

	current = *head;
	while (current->next)
	{
		current = current->next;
	}
	current->next = ajout;
}

t_tile	*init_decor(t_game *game, char *img, char type)
{
	t_tile	*new;

	new = ft_calloc(1, sizeof(t_tile));
	new->img = mlx_xpm_file_to_image(game->mlx, img, &new->x, &new->y);
	new->y = 0;
	new->x = 0;
	if (type == 'c' || type == 'w')
	{
		new->x = 100;
		new->y = 100;
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

int	main(int argc, char **argv)
{
	char	*map;
	t_game	*game;

	if (argc != 2)
		ft_exit("You must provide the path of the map, use: ./so_long <map>",
				1);
	game = ft_calloc(1, sizeof(t_game));
	map = argv[1];
	ft_check_map_size(map, &game);
	ft_check_tiles(open(map, O_RDONLY), &game);
	ft_check_tiles_value(open(map, O_RDONLY));
	game->title = "Le chien marin";
	game->decors = ft_calloc(1, sizeof(t_tile));
	ft_assign_tiles(&game, open(map, O_RDONLY));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height,
			game->title);
	mlx_hook(game->win, 2, 0, key_pressed, game);
	mlx_loop(game->mlx);
	return (0);
}
