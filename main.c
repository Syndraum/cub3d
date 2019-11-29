/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:53:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/29 13:18:10 by roalvare         ###   ########.fr       */
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
	// printf("pos  = (%.1f, %.1f)\n", game->ply.dir.x, game->ply.dir.y);
	set_image(&game.win.render, game.win.width, game.win.height, game.mlx);
	if (!(create_windows(&game.win, "cub3d")))
		return (EXIT_FAILURE);
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_hook(game.win.id, 2, 0, key_press_hook, &game);
	mlx_hook(game.win.id, 3, 0, key_release_hook, &game);
	mlx_hook(game.win.id, 17, 0, exit_hook, &game);
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
	event_exec(game);
	// print_map(game, 64);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win.id, game->win.render.id, 0, 0);
	return (1);
}

int	exit_hook(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win.id);
	exit(EXIT_SUCCESS);
}

int	key_press_hook(int keycode, t_game *game)
{
	printf("[KEY] = %d\n", keycode);
	fflush(stdout);
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->win.id);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 13)
		game->event[FORWARD] = 1;
	if (keycode == 1)
		game->event[BACKWARD] = 1;
	if (keycode == 0)
		game->event[LEFT] = 1;
	if (keycode == 2)
		game->event[RIGHT] = 1;
	if (keycode == 12 || keycode == 123)
		game->event[ROTATE_LEFT] = 1;
	if (keycode == 14 || keycode == 124)
		game->event[ROTATE_RIGHIT] = 1;
	return (1);
}

int	key_release_hook(int keycode, t_game *game)
{
	if (keycode == 13)
		game->event[FORWARD] = 0;
	if (keycode == 1)
		game->event[BACKWARD] = 0;
	if (keycode == 0)
		game->event[LEFT] = 0;
	if (keycode == 2)
		game->event[RIGHT] = 0;
	if (keycode == 12 || keycode == 123)
		game->event[ROTATE_LEFT] = 0;
	if (keycode == 14 || keycode == 124)
		game->event[ROTATE_RIGHIT] = 0;
	return (1);
}

void	move(t_game *game, double move_x, double move_y)
{
	if (game->map.map[(int)game->ply.y][(int)(game->ply.x - (move_x * MOVE_SPEED))] != '1')
		game->ply.x -= move_x * MOVE_SPEED;
	if (game->map.map[(int)(game->ply.y - (move_y * MOVE_SPEED))][(int)game->ply.x] != '1')
		game->ply.y -= move_y * MOVE_SPEED;
}

int	event_exec(t_game *game)
{	
	if (game->event[FORWARD])
		move(game, (-game->ply.dir.x), (-game->ply.dir.y));
	if (game->event[LEFT])
		move(game, (-game->ply.dir.y), (game->ply.dir.x));
	if (game->event[BACKWARD])
		move(game, (game->ply.dir.x), (game->ply.dir.y));
	if (game->event[RIGHT])
		move(game, (game->ply.dir.y), (-game->ply.dir.x));
	if (game->event[ROTATE_LEFT])
	{
		rotate_vector(&game->ply.dir, -ROT_SPEED);
		rotate_vector(&game->ply.plan, -ROT_SPEED);
	}
	 if (game->event[ROTATE_RIGHIT])
	{
		rotate_vector(&game->ply.dir, ROT_SPEED);
		rotate_vector(&game->ply.plan, ROT_SPEED);
	}
	return (1);
}
