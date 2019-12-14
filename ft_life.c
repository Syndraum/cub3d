/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:14:18 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/14 20:19:04 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	damage(t_game *game, double damage)
{
	game->ply.life -= damage;
	if (game->ply.life < 0)
		game->ply.life = 0;
}

void	heal(t_game *game, double heal)
{
	game->ply.life -= heal;
	if (game->ply.life > PLY_LIFE)
		game->ply.life = PLY_LIFE;
}
