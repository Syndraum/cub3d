/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:33:01 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 17:02:41 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	end_of_map(t_game *game, t_list *elmt)
{
	if (game->lst_maps->next != NULL)
	{
		game->map = game->lst_maps->next->content;
		elmt = game->lst_maps->next;
		ft_lstdelone(game->lst_maps, free_maps);
		game->lst_maps = elmt;
		set_ply(game);
	}
	else
		exit_hook(game);
}

static void	damage(t_game *game, int damage)
{
	game->ply.life += damage;
	if (game->ply.life < 0)
		game->ply.life = 0;
	if (game->ply.life > PLY_LIFE)
		game->ply.life = PLY_LIFE;
}

static void	effect(t_game *game, t_sprite *sprite, char *value)
{
	sprite = get_sprite(value, game);
	if (sprite->effect < 0 || game->ply.life != 100)
	{
		damage(game, sprite->effect);
		game->map->map[(int)game->ply.y][(int)game->ply.x] = '0';
	}
}

void		move(t_game *game, double move_x, double move_y)
{
	t_list		*elmt;
	t_vector	m;
	char		value;
	t_sprite	*stripe;

	m.x = move_x * MOVE_SPEED;
	m.y = move_y * MOVE_SPEED;
	elmt = NULL;
	stripe = NULL;
	value = game->map->map[(int)game->ply.y][(int)(game->ply.x - (m.x))];
	if (value != '1' && !issprite_wall(value, game->map))
		game->ply.x -= m.x;
	value = game->map->map[(int)(game->ply.y - (m.y))][(int)game->ply.x];
	if (value != '1' && !issprite_wall(value, game->map))
		game->ply.y -= m.y;
	value = game->map->map[(int)game->ply.y][(int)game->ply.x];
	if (issprite_damage(value, game->map))
		effect(game, stripe, &value);
	else if (issprite_end(value, game->map))
		end_of_map(game, elmt);
}
