/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:00:35 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/29 00:46:44 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"

typedef struct s_decors
{
	void			*img;
	int				x;
	int				y;
	char			type;
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

/* Prints the error message in the console. */
void				ft_error(char *message);
void				ft_check_map(char *map, t_decors **head, char therm,
						char type);
void				add_decors(t_decors **head, void *img, int x, int y,
						char type);

#endif