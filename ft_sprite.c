/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 18:11:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/02 19:15:27 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	add_vector(t_player *ply, double sprit_x, double sprit_y)
{
	int i;

	i = -1;
	while (ply->sprite[++i].x != -1)
		if (ply->sprite[i].x == sprit_x && ply->sprite[i].y == sprit_y)
			return (0);
	if (i > MAX_NBR_SPRITE)
		return (0);
	ply->sprite[i].x = sprit_x;
	ply->sprite[i].y = sprit_y;
	ply->sprite_dist[i] = (pow(ply->x - sprit_x, 2) + pow(ply->y - sprit_y, 2));
	ply->sprite[i + 1].x = -1.0;
	ply->sprite_dist[i + 1] = -1.0;
	// printf("sprite(%.1f, %.1f) %f\n", sprit_x, sprit_y, ply->sprite_dist[i]);
	return (1);
}

void	init_tabvector(t_player *ply)
{
	ply->sprite[0].x = -1.0;
	ply->sprite_dist[0] = -1.0;
}
