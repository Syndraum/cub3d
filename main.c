/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:53:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/15 13:04:24 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game		game;
	int			fd;

	if (argc < 2)
		return (ft_error(ENOENT));
	if (0 > (fd = open(argv[1], O_RDONLY)))
		return (ft_error(-1));
	if (!(game.mlx = mlx_init()))
		return (EXIT_FAILURE);
	game.win.mlx = game.mlx;
	if (!(set_map(fd, &game)))
		return (free_game(&game));
	game.ply.z_index = ft_calloc(sizeof(double), game.win.width);
	set_image(&game.win.render, game.win.width, game.win.height, game.mlx);
	if (argc == 3 && (!ft_strncmp(argv[2], "-save", 6)))
	{
		sreenshot(&game);
		return (free_game(&game));
	}
	if (!(create_windows(&game.win, "cub3d")))
		return (free_game(&game));
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_hook(game.win.id, 2, 0, key_press_hook, &game);
	mlx_hook(game.win.id, 3, 0, key_release_hook, &game);
	mlx_hook(game.win.id, 17, 0, exit_hook, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}

void	add_step_sprite(t_list *lst)
{
	t_sprite	*sprite;
	t_list		*cursor;

	cursor = lst;
	while(cursor != NULL)
	{
		sprite = (t_sprite*)cursor->content;
		sprite->step = (sprite->step + sprite->img.height) % sprite->img.width;
		cursor = cursor->next;
	}
}

int	loop_hook(t_game *game)
{
	event_exec(game);
	raycasting(game);
	add_step_sprite(game->map.sprite);
	mlx_put_image_to_window(game->mlx, game->win.id, game->win.render.id, 0, 0);
	return (1);
}
