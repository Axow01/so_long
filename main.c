/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:00:32 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/28 19:48:49 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "so_long.h"

typedef struct s_decors
{
	void			*img;
	int				x;
	int				y;
	struct t_decors	*next;
}					t_decors;

typedef struct s_playerpos
{
	void			*img;
	int				x;
	int				y;
}					t_playerpos;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	void			*img;
	t_playerpos		player;
	t_decors		*decors;
}					t_vars;

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
	if (!current->next)
		return ;
	current = current->next;
	while (current->next)
	{
		mlx_put_image_to_window(mlx, win, current->img, current->x, current->y);
		current = current->next;
	}
}

int	key_pressed(int keycode, t_vars *vars)
{
	int	speed;
	int	modifier;

	speed = 30;
	modifier = 1;
	modifier *= speed;
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

	newbitch = ft_calloc(1, sizeof(t_decors));
	newbitch->img = img;
	newbitch->x = x;
	newbitch->y = y;
	newbitch->next = NULL;
	(*head)->next = newbitch;
}

int	main(int argc, char **argv)
{
	t_decors	*chest;
	t_vars		vars;
	t_playerpos	player;
	char		*map;

	chest = ft_calloc(1, sizeof(t_decors));
	if (argc != 2)
		return (ft_error("You failed to provide args, -> ./so_long <map>"), 1);
	map = argv[1];
	vars.decors = chest;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Le chien marin");
	chest->img = mlx_xpm_file_to_image(vars.mlx, "sprites/chest.xpm", &chest->x,
			&chest->y);
	chest->x = 120;
	chest->y = 120;
	player.img = mlx_xpm_file_to_image(vars.mlx, "sprites/character.xpm",
			&player.x, &player.y);
	vars.img = player.img;
	chest->next = NULL;
	add_decors(&chest, chest->img, 800, 300);
	mlx_hook(vars.win, 2, 0, key_pressed, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
