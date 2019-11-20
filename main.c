/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:53:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/20 17:48:00 by roalvare         ###   ########.fr       */
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
		print_color(img, 0x45E7ad);
		mlx_put_image_to_window(windows->link_id, windows->id, img->id, 0, 0);
	}
	return (EXIT_SUCCESS);
}
