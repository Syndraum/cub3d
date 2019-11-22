/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:53:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/22 15:30:42 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char *argv[])
{
	void		*mlx;
	t_game		*game;
	int			fd;

	if (argc < 2)
		return (ft_error(ENOENT));
	else if (argc > 3)
		return (ft_error(E2BIG));
	if (0 > (fd = open(argv[1], O_RDONLY)))
		return (ft_error(-1));
	if (!(mlx = mlx_init()))
		return (EXIT_FAILURE);
	game = ft_calloc(sizeof(t_game), 1);
	game->win = ft_calloc(sizeof(t_windows), 1);
	game->win->mlx = mlx;
	if (!(game->map = ft_calloc(sizeof(t_map), 1)))
		return (0); //
	if (!(set_map(fd, game)))
		return(EXIT_FAILURE);
	ft_putendl_fd("[END]", 1);
	if (!(create_windows(game->win, "cub3d")))
		return (EXIT_FAILURE);
	mlx_key_hook(game->win->id, &key_hook, game->win);
	mlx_loop(mlx);
	// free_windows(windows);
	return (EXIT_SUCCESS);
}

int		ft_error(int error)
{
	if (error == -1 )
		perror("");
	else if (error <= 102)
		ft_putendl_fd(strerror(error), 2);
	return (EXIT_FAILURE);
}

int	key_hook(int keycode, void *param)
{	
	t_windows	*windows;

	windows = (t_windows*)param; 
	printf("[KEY] = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(windows->mlx, windows->id);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 0)
	{
		t_img *img = create_img(windows->mlx);
		set_image(img, windows->width, windows->height);
		print_color(img, 0xad5d95);
		mlx_put_image_to_window(windows->mlx, windows->id, img->id, 0, 0);
	}
	return (EXIT_SUCCESS);
}
