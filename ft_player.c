/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:08:30 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/23 13:06:28 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*creat_player(double x, double y)
{
	t_player *ply;

	if (!(ply = malloc(sizeof(t_player))))
		return (NULL);
	ply->x = x;
	ply->y = y;
	return (ply);
}
