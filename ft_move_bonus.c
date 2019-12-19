/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:33:01 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/19 18:15:01 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_game *game, double move_x, double move_y)
{
	t_vector	m;
	char		value;
	t_sprite	*stripe;

	m.x = move_x * MOVE_SPEED;
	m.y = move_y * MOVE_SPEED;
	value = game->map->map[(int)game->ply.y][(int)(game->ply.x - (m.x))];
	if (value != '1' && !issprite_wall(value, game->map))
		game->ply.x -= m.x;
	value = game->map->map[(int)(game->ply.y - (m.y))][(int)game->ply.x];
	if (value != '1' && !issprite_wall(value, game->map))
		game->ply.y -= m.y;
	value = game->map->map[(int)game->ply.y][(int)game->ply.x];
	if (issprite_damage(value, game->map))
	{
		stripe = get_sprite(&value, game);
		if (stripe->effect < 0 || game->ply.life != 100)
		{
			damage(game, stripe->effect);
			game->map->map[(int)game->ply.y][(int)game->ply.x] = '0';
		}
	}
	else if (issprite_end(value, game->map))
		exit_hook(game);
}
