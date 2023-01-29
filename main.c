/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:00:32 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/28 22:57:36 by mmarcott         ###   ########.fr       */
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
	ft_printf("reaching step one");
	current = current->next;
	while (current)
	{
		ft_printf("X: %d Y: %d\n", current->x, current->y);
		mlx_put_image_to_window(mlx, win, current->img, current->x, current->y);
		if (current->next == NULL)
			return ;
		current = current->next;
	}
}

int	key_pressed(int keycode, t_vars *vars)
{
	int	speed;
	int	modifier;

	speed = 30;
	modifier = 1;
	modifier = 100;
	ft_printf("%d\n", keycode);
	mlx_clear_window(vars->mlx, vars->win);
	place_decor(vars->decors, vars);
	if (keycode == 2) // d
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->player.x
				+= modifier, vars->player.y);
	else if (keycode == 1) // s
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->player.x,
				vars->player.y += modifier);
	else if (keycode == 0) // a
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->player.x
				-= modifier, vars->player.y);
	else if (keycode == 13)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->player.x,
				vars->player.y -= modifier);
	else if (keycode == 15)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img,
				vars->player.x = 10, vars->player.y = 10);
	else if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->player.x,
				vars->player.y);
	return (0);
}

void	add_decors(t_decors **head, void *img, int x, int y)
{
	t_decors	*newbitch;
	t_decors	*current;

	current = *head;
	newbitch = ft_calloc(1, sizeof(t_decors));
	newbitch->img = img;
	newbitch->x = x;
	newbitch->y = y;
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
		current = current->next;
	current->next = ajout;
}

int	main(int argc, char **argv)
{
	t_decors	*water;
	t_decors	*sand;
	t_decors	*chest;
	t_vars		vars;
	t_playerpos	player;
	char		*map;

	sand = ft_calloc(1, sizeof(t_decors));
	water = ft_calloc(1, sizeof(t_decors));
	chest = ft_calloc(1, sizeof(t_decors));
	if (argc != 2)
		return (ft_error("You failed to provide args, -> ./so_long <map>"), 1);
	map = argv[1];
	vars.decors = sand;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1900, 1000, "Le chien marin");
	player.img = mlx_xpm_file_to_image(vars.mlx, "sprites/character.xpm",
			&player.x, &player.y);
	vars.img = player.img;
	sand->img = mlx_xpm_file_to_image(vars.mlx, "sprites/sand.xpm", &sand->x,
			&sand->y);
	water->img = mlx_xpm_file_to_image(vars.mlx, "sprites/water.xpm", &water->x,
			&water->y);
	chest->img = mlx_xpm_file_to_image(vars.mlx, "sprites/chest.xpm", &chest->x,
			&chest->y);
	ft_printf("before checkmap\n");
	ft_check_map(map, &sand, '1');
	ft_check_map(map, &water, '0');
	ft_check_map(map, &chest, 'C');
	add_end_list(&sand, water);
	add_end_list(&sand, chest);
	place_decor(sand, &vars);
	mlx_hook(vars.win, 2, 0, key_pressed, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
