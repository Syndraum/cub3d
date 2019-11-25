/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:53:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/25 19:55:10 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char *argv[])
{
	t_game		game;
	int			fd;

	if (argc < 2)
		return (ft_error(ENOENT));
	else if (argc > 3)
		return (ft_error(E2BIG));
	if (0 > (fd = open(argv[1], O_RDONLY)))
		return (ft_error(-1));
	if (!(game.mlx = mlx_init()))
		return (EXIT_FAILURE);
	game.win.mlx = game.mlx;
	if (!(set_map(fd, &game)))
		return(EXIT_FAILURE);
	set_image(&game.win.render, game.win.width, game.win.height, game.mlx);
	if (!(create_windows(&game.win, "cub3d")))
		return (EXIT_FAILURE);
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_key_hook(game.win.id, key_hook, &game);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_loop(game.mlx);
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

int	loop_hook(t_game *game)
{
	print_map(game, 64);
	mlx_put_image_to_window(game->mlx, game->win.id, game->win.render.id, 0, 0);
	return (1);
}

int	key_hook(int keycode, t_game *game)
{	
	printf("[KEY] = %d\n", keycode);
	fflush(stdout);
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->win.id);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 13)
		game->ply.y -= 0.2;
	else if (keycode == 0)
		game->ply.x -= 0.2;
	else if (keycode == 1)
		game->ply.y += 0.2;
	else if (keycode == 2)
		game->ply.x += 0.2;
	else if (keycode == 14)
	{
		rotate_vector(&game->ply.dir, -0.1);
		rotate_vector(&game->ply.plan, -0.1);
		printf("dir(%f, %f)\tplan(%f, %f)\n", game->ply.dir.x, game->ply.dir.y, game->ply.plan.x, game->ply.plan.y);
		fflush(stdout);
	}
	else if (keycode == 12)
	{
		rotate_vector(&game->ply.dir, 0.1);
		rotate_vector(&game->ply.plan, 0.1);
	}
	return (1);
}
