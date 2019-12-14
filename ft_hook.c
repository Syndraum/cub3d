/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:53:16 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/14 20:21:50 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_hook(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win.id);
	exit(free_map(game->map.map));
}

int		key_press_hook(int keycode, t_game *game)
{
	printf("[KEY] = %d\n", keycode);
	fflush(stdout);
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

void	move(t_game *game, double move_x, double move_y)
{
	double m_x;
	double m_y;

	m_x = move_x * MOVE_SPEED;
	m_y = move_y * MOVE_SPEED;
	if (BONUS)
	{
		if (game->map.map[(int)game->ply.y][(int)(game->ply.x - (m_x))] != '1')
			game->ply.x -= m_x;
		if (game->map.map[(int)(game->ply.y - (m_y))][(int)game->ply.x] != '1')
			game->ply.y -= m_y;
	}
	else
	{
		if ((game->ply.x - (m_x)) > 1 &&
		(game->ply.x - (m_x)) < ft_strlen(game->map.map[0]) - 1)
			game->ply.x -= m_x;
		if ((game->ply.y - (m_y)) > 1 &&
		(game->ply.y - (m_y)) < ft_tablen(game->map.map) - 1)
			game->ply.y -= m_y;
	}
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
