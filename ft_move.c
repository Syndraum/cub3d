/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:24:36 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/18 17:28:05 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_game *game, double move_x, double move_y)
{
	t_vector	m;

	m.x = move_x * MOVE_SPEED;
	m.y = move_y * MOVE_SPEED;

	if ((game->ply.x - (m.x)) > 1 &&
	(game->ply.x - (m.x)) < ft_strlen(game->map.map[0]) - 1)
		game->ply.x -= m.x;
	if ((game->ply.y - (m.y)) > 1 &&
	(game->ply.y - (m.y)) < ft_tablen(game->map.map) - 1)
		game->ply.y -= m.y;
}
