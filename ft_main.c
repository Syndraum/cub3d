/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:53:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 17:53:36 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char *argv[])
{
	t_game		game;
	int			fd;
	int			result;

	if (argc < 2)
		return (ft_error(ENOENT));
	if (0 > (fd = open(argv[1], O_RDONLY)))
		return (ft_error(-1));
	if (!(game.mlx = mlx_init()))
		return (ft_error(-1));
	init_game(&game, &result);
	while (0 < result)
		result = set_map(fd, &game);
	if (result == -1)
		return (free_game(&game));
	setup_game(&game);
	if (argc >= 3 && (!ft_strncmp(argv[2], "-save", 6)))
	{
		sreenshot(&game);
		return (free_game(&game));
	}
	if (!(create_windows(&game.win, "cub3d")))
		return (free_game(&game));
	set_hook(&game);
	return (EXIT_SUCCESS);
}

void	init_game(t_game *game, int *result)
{
	int i;

	i = -1;
	game->win.mlx = game->mlx;
	game->win.height = 0;
	game->win.width = 0;
	game->lst_maps = NULL;
	game->map = NULL;
	set_xmp(&game->minimap.img, "./assets/minimap.xpm", game->mlx);
	set_xmp(&game->jauge.jauge, "assets/jauge.xpm", game->mlx);
	set_xmp(&game->jauge.life, "assets/life.xpm", game->mlx);
	init_player(&game->ply);
	while (++i < ESCAPE)
		game->event[i] = 0;
	*result = 1;
}

void	set_hook(t_game *game)
{
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_hook(game->win.id, 2, 0, key_press_hook, game);
	mlx_hook(game->win.id, 3, 0, key_release_hook, game);
	mlx_hook(game->win.id, 17, 0, exit_hook, game);
	mlx_loop(game->mlx);
}

void	setup_game(t_game *game)
{
	game->map = game->lst_maps->content;
	set_ply(game);
	game->ply.z_index = ft_calloc(sizeof(double), game->win.width);
	set_image(&game->win.render, game->win.width, game->win.height, game->mlx);
}

int		loop_hook(t_game *game)
{
	if (game->ply.life <= 0)
		exit_hook(game);
	event_exec(game);
	raycasting(game);
	add_step_sprite(game->map->sprite);
	mlx_put_image_to_window(game->mlx, game->win.id, game->win.render.id, 0, 0);
	return (1);
}
