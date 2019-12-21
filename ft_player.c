/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:08:30 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 15:19:17 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->life = 100;
	player->x = 0;
	player->y = 0;
	set_vector(&player->dir, 0, 1);
	set_vector(&player->plan, FOV, 0);
}

void	set_dir(t_player *player, double x, double y)
{
	set_vector(&player->dir, x, y);
	if (x == 0 && y == 1)
		set_vector(&player->plan, -FOV, 0);
	else if (x == 0 && y == -1)
		set_vector(&player->plan, FOV, 0);
	else if (x == 1 && y == 0)
		set_vector(&player->plan, 0, FOV);
	else if (x == -1 && y == 0)
		set_vector(&player->plan, 0, -FOV);
}

void	set_ply(t_game *game)
{
	char dir;

	dir = game->map->dir;
	game->ply.x = game->map->pos.x;
	game->ply.y = game->map->pos.y;
	if (dir == 'N')
		set_dir(&game->ply, 0, -1);
	else if (dir == 'S')
		set_dir(&game->ply, 0, 1);
	else if (dir == 'E')
		set_dir(&game->ply, 1, 0);
	else if (dir == 'W')
		set_dir(&game->ply, -1, 0);
}

void	set_vector(t_vector *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

void	rotate_vector(t_vector *vector, double speed)
{
	double tmp;

	tmp = vector->x;
	vector->x = vector->x * cos(speed) - vector->y * sin(speed);
	vector->y = tmp * sin(speed) + vector->y * cos(speed);
}
