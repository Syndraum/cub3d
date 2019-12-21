/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:14:18 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 17:01:18 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	damage(t_game *game, int damage)
// {
// 	game->ply.life += damage;
// 	if (game->ply.life < 0)
// 		game->ply.life = 0;
// 	if (game->ply.life > PLY_LIFE)
// 		game->ply.life = PLY_LIFE;
// }

void	strmv_wh(char **line, char c)
{
	while (**line == c)
		(*line)++;
}

void	strmv_if(char **line, char c)
{
	if (**line == c)
		(*line)++;
}
