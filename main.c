/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:00:32 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/26 16:18:13 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(char *message)
{
	ft_printf("Error: %s\n", message);
}

int	main(int argc, char **argv)
{
	char	*map;
	int		fd;

	if (argc != 2)
		return (ft_error("You failed to provide args, -> ./so_long <map>"), 1);
	map = argv[1];
	fd = open("testfile.txt", O_RDONLY);
	ft_printf("%s", get_next_line(fd));
	return (0);
}
