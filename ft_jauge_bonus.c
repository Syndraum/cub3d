/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jauge_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 17:08:48 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 17:09:49 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	rgbcmp(char *cursor, t_rgb *rgb)
{
	if (rgb->red != *(cursor + 2))
		return (0);
	else if (rgb->green != *(cursor + 1))
		return (0);
	else if (rgb->blue != *cursor)
		return (0);
	return (1);
}

void	set_rgb(t_rgb *rgb, char red, char green, char blue)
{
	rgb->red = red;
	rgb->green = green;
	rgb->blue = blue;
	rgb->alpha = 0;
}

void	init_jauge(t_jauge *jauge, t_minimap *map, t_game *game)
{
	jauge->height = game->win.height / 25;
	jauge->widht = game->win.width / 3.5;
	jauge->del.x = (double)jauge->jauge.width / jauge->widht;
	jauge->del.y = (double)jauge->jauge.height / jauge->height;
	jauge->crs_j = jauge->jauge.data;
	jauge->crs_l = jauge->jauge.data;
	jauge->pi.x = map->height + 2 * map->padding;
	jauge->tmp.x = 0;
	jauge->tmp.y = 0;
}

void	print_jauge(t_jauge *j, t_minimap *map, t_game *game)
{
	while (j->tmp.x < j->jauge.width)
	{
		j->pi.y = 2 * map->padding;
		j->tmp.y = 0;
		while (j->tmp.y < j->jauge.height)
		{
			j->crs_j = get_img_pixel(&j->jauge, (int)j->tmp.x, (int)j->tmp.y);
			j->crs_l = get_img_pixel(&j->life, (int)j->tmp.x, (int)j->tmp.y);
			if (*(j->crs_l + 3) == 0 &&
			100 * j->tmp.x / j->jauge.width < game->ply.life)
				img_pixel_cpy(&game->win.render, j->pi.x, j->pi.y, j->crs_l);
			else if (*(j->crs_j + 3) == 0)
				img_pixel_cpy(&game->win.render, j->pi.x, j->pi.y, j->crs_j);
			j->tmp.y += j->del.y;
			(j->pi.y)++;
		}
		(j->pi.x)++;
		j->tmp.x += j->del.x;
	}
}
