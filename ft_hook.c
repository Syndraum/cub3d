/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:53:16 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/19 18:00:39 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_hook(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win.id);
	exit(free_map(game->map->map));
}

int		key_press_hook(int keycode, t_game *game)
{
	if (keycode == 53)
		exit_hook(game);
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

int		key_release_hook(int keycode, t_game *game)
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

int		event_exec(t_game *game)
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
