/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skybox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:46:11 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/08 19:46:02 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skybox(t_game *game, t_ray *ray, int x)
{
	t_img		*img;
	t_vector	cursor;
	t_coord		pixel;
	double		offset;
	double		dif_angle;
	int			y;

	img = &game->map.skybox;
	dif_angle = ((double)img->width * (atan2(0, -1) - atan2(game->ply.dir.x, game->ply.dir.y))) / M_PI;
	cursor.y = 0;
	pixel.x = (int)dif_angle + (int)(x * ((double)img->width) / (double)game->win.width / 4) % img->width;
	offset = (double)img->height / (((double)game->win.height / 2.0));
	y = 0;
	if (ray->pixel_start < 0)
		ray->pixel_start = 0;
	while (y < ray->pixel_start)
	{
		pixel.y = (int)cursor.y;
		img_pixel_cpy(&game->win.render, x, y, get_img_pixel(img, pixel.x, pixel.y));
		cursor.y += offset;
		y++;
	}
}
