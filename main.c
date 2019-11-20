/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:53:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/20 14:41:34 by roalvare         ###   ########.fr       */
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
		void *img = mlx_new_image(windows->link_id, windows->width, windows->height);
		// print_line(windows, img, 200)
		// print_color(windows, 0x45E7ad);
		mlx_put_image_to_window(windows->link_id, windows->id, img, 0, 0);
	}
	return (EXIT_SUCCESS);
}

void	print_line(t_windows *windows, void *img, int line, int color)
{
	int i;

	i = -1;
	while (++i < windows->width)
		mlx_pixel_put(windows->link_id, img, i, line, color);
}

void 	print_colunm(t_windows *windows, int colunm, int color)
{
	int i;

	i = -1;
	while (++i < windows->height)
		mlx_pixel_put(windows->link_id, windows->id, colunm, i, color);
}

void	print_color(t_windows *windows, int color)
{
	int x;

	x = -1;
	while (++x < windows->width)
		print_colunm(windows, x, color);
}
