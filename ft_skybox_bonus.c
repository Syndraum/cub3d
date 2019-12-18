/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skybox_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:46:11 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/18 19:08:36 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skybox(t_game *game, t_ray *ray, int x)
{
	t_img		*img;
	t_vector	cursor;
	t_coord		pi;
	double		offset;
	int			y;

	img = &game->map.skybox;
	cursor.y = 0;
	pi.x = (int)(x * ((double)img->width) / (double)game->win.width);
	pi.x = (int)((ray->angle + pi.x) / 2) % img->width;
	offset = (double)img->height / (((double)game->win.height / 2.0));
	y = 0;
	if (ray->pixel_start < 0)
		ray->pixel_start = 0;
	while (y <= ray->pixel_start)
	{
		pi.y = (int)cursor.y;
		img_pixel_cpy(&game->win.render, x, y, get_img_pixel(img, pi.x, pi.y));
		cursor.y += offset;
		y++;
	}
}
