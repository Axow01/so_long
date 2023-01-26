/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 01:17:29 by mmarcott          #+#    #+#             */
/*   Updated: 2022/12/16 13:17:51 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
void	cleanup_stash(char **stash, char *line);
void	*ft_free(char *p);
void	finalise(char **line, char **stash);
void	put_line(char **line, char *stash);
char	*ft_calloc(size_t nmemb, size_t size);

#endif
