/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:00:32 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/29 01:58:00 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "so_long.h"

void	ft_error(char *message)
{
	ft_printf("Error: %s\n", message);
}

void	place_decor(t_decors *decs, t_vars *valeur)
{
	void		*mlx;
	void		*win;
	t_decors	*current;

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

int	check_list(t_decors *head, int x, int y)
{
	t_decors	*current;

	current = head;
	while (current->next)
	{
		if (current->type == 's' && x == current->x && y == current->y)
			return (1);
		current = current->next;
	}
	return (0);
}

void	move_player(t_vars *vars, int xmodifier, int ymodifier)
{
	if (!check_list(vars->decors, vars->player.x + xmodifier, vars->player.y
			+ ymodifier))
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->player.img,
				vars->player.x += xmodifier, vars->player.y += ymodifier);
	}
	else
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->player.img, vars->player.x,
				vars->player.y);
	}
}

int	key_pressed(int keycode, t_vars *vars)
{
	int	modifier;

	modifier = 100;
	mlx_clear_window(vars->mlx, vars->win);
	place_decor(vars->decors, vars);
	if (keycode == 2) // d
		move_player(vars, 100, 0);
	else if (keycode == 1) // s
		move_player(vars, 0, 100);
	else if (keycode == 0) // a
		move_player(vars, -100, 0);
	else if (keycode == 13)
		move_player(vars, 0, -100);
	else if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->player.img,
				vars->player.x, vars->player.y);
	return (0);
}

void	add_decors(t_decors **head, void *img, int x, int y, char type)
{
	t_decors	*newbitch;
	t_decors	*current;

	current = *head;
	newbitch = ft_calloc(1, sizeof(t_decors));
	newbitch->img = img;
	newbitch->x = x;
	newbitch->y = y;
	newbitch->type = type;
	newbitch->next = NULL;
	while (current->next)
		current = current->next;
	current->next = newbitch;
}

void	add_end_list(t_decors **head, t_decors *ajout)
{
	t_decors	*current;

	current = *head;
	while (current->next)
	{
		current = current->next;
	}
	current->next = ajout;
}

t_decors	*init_decor(t_vars *vars, char *img, char type)
{
	t_decors	*new;

	new = ft_calloc(1, sizeof(t_decors));
	new->img = mlx_xpm_file_to_image(vars->mlx, img, &new->x, &new->y);
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
	t_decors	*water;
	t_decors	*sand;
	t_decors	*chest;
	t_vars		vars;
	t_playerpos	player;
	char		*map;

	if (argc != 2)
		return (ft_error("You failed to provide args, -> ./so_long <map>"), 1);
	map = argv[1];
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1900, 1000, "Le chien marin");
	player.img = mlx_xpm_file_to_image(vars.mlx, "sprites/character.xpm",
			&vars.player.x, &vars.player.y);
	player.x = 300;
	player.y = 300;
	vars.player = player;
	sand = init_decor(&vars, "sprites/sand.xpm", 's');
	water = init_decor(&vars, "sprites/water.xpm", 'w');
	chest = init_decor(&vars, "sprites/chest.xpm", 'c');
	ft_check_map(map, &sand, '1', 's');
	ft_check_map(map, &water, '0', 'w');
	ft_check_map(map, &chest, 'C', 'c');
	add_end_list(&sand, water);
	add_end_list(&sand, chest);
	vars.decors = sand;
	place_decor(sand, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, player.img, player.x, player.y);
	mlx_hook(vars.win, 2, 0, key_pressed, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
