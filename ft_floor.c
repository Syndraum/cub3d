/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:13:51 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/04 16:54:22 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_casting(t_game *game, t_ray *ray, int x)
{
	t_vector 	floorwall;
	t_vector 	currentfloor;
	t_coord		floortext;
	t_img		*img;
	double		distwall;
	double		distply;
	double		currentdist;
	double		weight;

	img = &game->map.east;
	if (ray->wall == 2)
	{
		floorwall.x = ray->map.x;
		floorwall.y = ray->map.y + ray->wall_x;
	}
	else if (ray->wall == 0)
	{
		floorwall.x = ray->map.x + 1.0;
		floorwall.y = ray->map.y + ray->wall_x;
	}
	else if (ray->wall == 3)
	{
		floorwall.x = ray->map.x + ray->wall_x;
		floorwall.y = ray->map.y;
	}
	else if (ray->wall == 1)
	{
		floorwall.x = ray->map.x + ray->wall_x;
		floorwall.y = ray->map.y + 1.0;
	}
	distwall = ray->len;
	distply = 0.0;
	if (ray->pixel_end < 0)
		ray->pixel_end = game->win.height;
	int y = ray->pixel_end + 1;
	while (y < game->win.height)
	{
		currentdist = game->win.height / (2.0 * y - game->win.height);
		weight = (currentdist - distply) / (distwall - distply);
		currentfloor.x = weight * floorwall.x + (1.0 - weight) * game->ply.x;
		currentfloor.y = weight * floorwall.y + (1.0 - weight) * game->ply.y;
		floortext.x = (int)(currentfloor.x * img->width) % img->width;
		floortext.y = (int)(currentfloor.y * img->height) % img->height;
		img_pixel_cpy(&game->win.render, x, y, get_img_pixel(img, floortext.x, floortext.y));
		y++;
	}
}
