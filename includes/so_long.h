/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:00:35 by mmarcott          #+#    #+#             */
/*   Updated: 2023/05/05 13:37:21 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
//# include <mlx.h>
# include "mlx/mlx.h"

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
	int				collected_c;
	int				moved;
	char			**map;
	void			*chest;
	void			*sand;
	void			*water;
	void			*exit;
	void			*playerimg;
	int				c_count;
	int				e_count;
}					t_game;

/* Prints a message, and then exit the program with the error type or not. */
void				ft_exit(char *message, int error);
/* This function add a new node to the tiles node. */
void				add_decors(t_game *game, int x, int y, char type);
/* Check the map if it is valid of not valid == 1. */
int					ft_check_map_size(t_game *game, int fd);
/* Checks map name correct extension. .ber */
int					ft_check_name(char *map);
/* This function checks for the map values to see if they are right. */
void				ft_check_tiles(int fd, t_game *game);
/* check a single line. */
int					ft_check_line(char *line, char check, int all);
/* check the value of all characters in the map. (COLLECTIBLES, EXITS,
		PLAYERS) */
void				ft_check_tiles_value(int fd, t_game *game);
/* This function convert the map into a char table. */
char				**ft_convert_map(int fd, t_game *game);
/* This function create the decors of the map. (walls, background, chest ,
		player, exits) */
void				ft_create_decors(t_tile **tiles, t_game *game, char **map);
/* ... */
void				ft_move_player(t_game *game, int modifierx, int modifiery);
/* flood fill recursive function. */
void				ft_flood_init(char **map, t_game *game);
/* Check player movement for colisions. */
int					ft_check_moving_point(t_game *game, int x, int y);
/* Delete a tile. */
void				ft_delete_tile(t_tile *tile, int x, int y, char type);
/* Free a 2d array. */
void				ft_free_darray(char **array, int height);
/* Free all the structs. */
void				ft_exit_free(t_game *game, char *string);
/* This function checks for the type of the tiles and then add a new tiles
with this tiles. */
void				ft_check_tile_type(t_game *game, int col, int row,
						char **map);
/* This function counts tiles. */
void				ft_count_tiles(int *player, int *exit, char line,
						t_game *game);
/* This init the make dans the flood fill. */
void				ft_init_map(t_game *game, char *mapn);
/* Qutit close button. */
int					ft_quitt(t_game *game);
#endif
