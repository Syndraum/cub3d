/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:13:51 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 18:45:47 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_beginfloor(t_ray *ray, t_vector *floor)
{
	if (ray->wall == 2)
	{
		floor->x = ray->map.x;
		floor->y = ray->map.y + ray->wall_x;
	}
	else if (ray->wall == 0)
	{
		floor->x = ray->map.x + 1.0;
		floor->y = ray->map.y + ray->wall_x;
	}
	else if (ray->wall == 3)
	{
		floor->x = ray->map.x + ray->wall_x;
		floor->y = ray->map.y;
	}
	else if (ray->wall == 1)
	{
		floor->x = ray->map.x + ray->wall_x;
		floor->y = ray->map.y + 1.0;
	}
}

static void	printfloor(t_floor *f, t_ray *ray, t_game *game, int x)
{
	int		y;
	t_img	*img;
	char	*cursor;

	img = &game->map->floor_text;
	if (ray->pixel_end < 0)
		ray->pixel_end = game->win.height;
	y = ray->pixel_end;
	while (y < game->win.height)
	{
		f->dist_c = game->win.height / (2.0 * (y + 1) - game->win.height);
		f->weight = (f->dist_c - f->dist_p) / (f->dist_w - f->dist_p);
		f->curr.x = f->weight * f->init.x + (1.0 - f->weight) * game->ply.x;
		f->curr.y = f->weight * f->init.y + (1.0 - f->weight) * game->ply.y;
		f->text.x = (int)(f->curr.x * img->width) % img->width;
		f->text.y = (int)(f->curr.y * img->height) % img->height;
		cursor = get_img_pixel(img, f->text.x, f->text.y);
		img_pixel_cpy(&game->win.render, x, y, cursor);
		y++;
	}
}

void		floor_casting(t_game *game, t_ray *ray, int x)
{
	t_floor	floor;

	set_beginfloor(ray, &floor.init);
	floor.dist_w = ray->len;
	floor.dist_p = 0.0;
	printfloor(&floor, ray, game, x);
}
