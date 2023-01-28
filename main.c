/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:00:32 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/28 15:45:06 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "so_long.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	ft_error(char *message)
{
	ft_printf("Error: %s\n", message);
}

/* Modify a pixel in an image. */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	char	*map;
	int		fd;
	void	*mlx;
	void	*windows;
	t_data	img;
	int		wid;
	int		height;
	int		x;
	int		y;
	t_data	chest;

	y = 10;
	x = 10;
	if (argc != 2)
		return (ft_error("You failed to provide args, -> ./so_long <map>"), 1);
	map = argv[1];
	mlx = mlx_init();
	windows = mlx_new_window(mlx, 1920, 1080, "SO_LONG");
	img.img = mlx_xpm_file_to_image(mlx, "sprites/perso.xpm", &wid, &height);
	chest.img = mlx_xpm_file_to_image(mlx, "sprites/chest.xpm", &wid, &height);
	mlx_put_image_to_window(mlx, windows, img.img, 120, 160);
	mlx_put_image_to_window(mlx, windows, chest.img, 560, 160);
	ft_printf("X: %d - Y: %d\n", wid, height);
	mlx_loop(mlx);
	return (0);
}
