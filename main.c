/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:53:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/20 17:01:56 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char *argv[])
{
	void		*link_id;
	t_windows	*windows;

	if (argc < 2)
	{
		perror(strerror(1));
		return(EXIT_FAILURE);
	}
	(void)argv;
	if (!(link_id = mlx_init()))
		return (EXIT_FAILURE);
	if (!(windows = create_windows(link_id, 1080, 720, "cub3d")))
		return (EXIT_FAILURE);
	// print_color(windows, 0x45E7ad);
	mlx_key_hook(windows->id, &key_hook, windows);
	mlx_loop(link_id);
	free_windows(windows);
	return (EXIT_SUCCESS);
}

t_windows	*create_windows(void *link_id, int width, int height, char *title)
{
	t_windows	*windows;
	
	if (!(windows = malloc(sizeof(t_windows))))
		return (NULL);
	if (!(windows->id = mlx_new_window(link_id, width, height, title)))
		return (free_windows(windows));
	windows->width = width;
	windows->height = height;
	windows->link_id = link_id;
	return (windows);
}

t_img	*create_img(void *mlx, int width, int height)
{
	t_img	*img;
	
	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	if (!(img->id = mlx_new_image(mlx, width, height)))
		return (NULL); //
	img->width = width;
	img->height = height;
	return (img);
}

void	*free_windows(t_windows	*windows)
{
	free(windows);
	return (NULL);
}

int	key_hook(int keycode, void *param)
{	
	t_windows	*windows;

	windows = (t_windows*)param; 
	printf("[KEY] = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(windows->link_id, windows->id);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 0)
	{
		t_img *img = create_img(windows->link_id, windows->width, windows->height);
		print_color(img, windows->link_id, 0x45E7ad);
		// print_color(windows, 0x45E7ad);
		mlx_put_image_to_window(windows->link_id, windows->id, img->id, 0, 0);
	}
	return (EXIT_SUCCESS);
}

void	img_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*begin;
	int		bpp;
	int		size_l;
	int		endian;

	begin = mlx_get_data_addr(img->id, &bpp, &size_l, &endian);
	begin += (y * size_l);
	begin += (x * bpp / (sizeof(char) * 8));  
	*begin = color;
	*(begin + 1) = color / 256 ;
	*(begin + 2) = color / 256 / 256;
}

void 	print_colunm(t_img *img, void *mlx, int colunm, int color)
{
	int 			i;
	unsigned int	u_color;

	u_color = mlx_get_color_value(mlx, color);
	i = -1;
	while (++i < img->height)
		img_pixel_put(img, colunm, i, u_color);
}

void	print_line(t_windows *windows, void *img, int line, int color)
{
	int i;

	i = -1;
	while (++i < windows->width)
		mlx_pixel_put(windows->link_id, img, i, line, color);
}

void	print_color(t_img *img, void *mlx, int color)
{
	int x;

	x = -1;
	while (++x < img->width)
		print_colunm(img, mlx , x, color);
}
