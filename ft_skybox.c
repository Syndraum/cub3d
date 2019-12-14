/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skybox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:46:11 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/14 13:00:59 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_anglediff(t_game *game)
{
	return (atan2(0, -1) - atan2(game->ply.dir.x, game->ply.dir.y));
}

void	skybox(t_game *game, t_ray *ray, int x)
{
	t_img		*img;
	t_vector	cursor;
	t_coord		pi;
	double		offset;
	int			y;

	img = &game->map.skybox;
	cursor.y = 0;
	pi.x = (int)(x * ((double)img->width) / (double)game->win.width / 4);
	pi.x = (int)ray->angle + pi.x % img->width;
	offset = (double)img->height / (((double)game->win.height / 2.0));
	y = 0;
	if (ray->pixel_start < 0)
		ray->pixel_start = 0;
	while (y < ray->pixel_start)
	{
		pi.y = (int)cursor.y;
		img_pixel_cpy(&game->win.render, x, y, get_img_pixel(img, pi.x, pi.y));
		cursor.y += offset;
		y++;
	}
}
