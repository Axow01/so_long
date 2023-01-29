/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:00:35 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/29 17:16:27 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <mlx.h>

typedef struct s_tile
{
	void			*img;
	int				x;
	int				y;
	char			type;
	struct s_tile	*next;
}					t_tile;

typedef struct s_player
{
	void			*img;
	int				x;
	int				y;
}					t_player;

typedef struct s_game
{
	char			*title;
	int				width;
	int				height;
	void			*mlx;
	void			*win;
	t_tile			*decors;
	t_player		*player;
}					t_game;

/* Prints the error message in the console. */
void				ft_error(char *message);
/* Prints a message, and then exit the program with the error type or not. */
void				ft_exit(char *message, int error);
/* This function add a new node to the tiles node. */
void				add_decors(t_tile **head, void *img, int x, int y,
						char type);
/* This function create the map textures after the map as been checked. */
void				ft_create_map(char *map, t_tile **head, char therm,
						char type);
/* Check the map if it is valid of not valid == 1. */
int					ft_check_map(char *map, t_game **game);

#endif