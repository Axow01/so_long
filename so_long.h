/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:00:35 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/20 13:39:34 by mmarcott         ###   ########.fr       */
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

/* Prints a message, and then exit the program with the error type or not. */
void				ft_exit(char *message, int error);
/* This function add a new node to the tiles node. */
void				add_decors(t_tile **head, void *img, int x, int y,
						char type);
/* Check the map if it is valid of not valid == 1. */
int					ft_check_map_size(char *map, t_game **game);
/* This function checks for the map values to see if they are right. */
void				ft_check_tiles(int fd, t_game **game);
/* check a single line. */
int					ft_check_line(char *line, char check, int all);
/* check the value of all characters in the map. (COLLECTIBLES, EXITS,
		PLAYERS) */
void				ft_check_tiles_value(int fd);
/* This function convert the map into a char table. */
char				**ft_convert_map(int fd, t_game **game);
/* This function checks that collectibles and exits are accessible. */
void				ft_playable(char **map, t_game **game);
/* This function create the decors of the map. (walls, background, chest , player, exits) */
void				ft_create_decors(t_tile **tiles, t_game **game, char **map);
#endif