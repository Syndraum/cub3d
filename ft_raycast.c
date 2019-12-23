/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 11:10:00 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/23 11:57:57 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*get_side_texture(t_map *map, char side)
{
	if (side == 0)
		return (&map->west);
	else if (side == 1)
		return (&map->north);
	else if (side == 2)
		return (&map->east);
	else if (side == 3)
		return (&map->south);
	return (NULL);
}

static void		drawray(t_game *game, t_ray *ray, int line)
{
	int		i;
	int		j;
	int		y;
	t_img	*img;
	char	*pixel;

	i = ray->pixel_start - 1;
	j = ray->pixel_start;
	img = get_side_texture(game->map, ray->side_w);
	while (++i < ray->pixel_end)
	{
		y = i * 2 - game->win.height + ray->line_h;
		ray->text.x = ray->wall_x * img->width;
		ray->text.y = y * img->height / ray->line_h / 2;
		pixel = get_img_pixel(img, ray->text.x, ray->text.y);
		img_pixel_cpy(&game->win.render, line, i, pixel);
	}
	floor_casting(game, ray, line);
	skybox(game, ray, line);
}

static void		set_pixelcord(t_game *game, t_ray *ray)
{
	ray->line_h = (int)(game->win.height / ray->len);
	ray->pixel_start = game->win.height / 2 - ray->line_h / 2;
	if (ray->pixel_start < 0)
		ray->pixel_start = 0;
	ray->pixel_end = game->win.height / 2 + ray->line_h / 2;
	if (ray->pixel_end >= game->win.height)
		ray->pixel_end = game->win.height - 1;
	if (ray->side_w % 2)
		ray->wall_x = game->ply.x + ray->len * ray->ray.x;
	else
		ray->wall_x = game->ply.y + ray->len * ray->ray.y;
	ray->wall_x -= floor(ray->wall_x);
}

static double	get_anglediff(t_game *game)
{
	return (atan2(0, -1) - atan2(game->ply.dir.x, game->ply.dir.y));
}

void			raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = -1;
	game->ply.object = NULL;
	ray.angle = (double)(game->map->skybox.width) *
	(get_anglediff(game) / M_PI);
	while (++x < game->win.width)
	{
		init_ray(&ray, game, x);
		exec_dda(&ray, game);
		set_pixelcord(game, &ray);
		drawray(game, &ray, x);
		game->ply.z_wall[x] = ray.len;
	}
	put_sprite(game);
	hud(game);
	ft_lstclear(&game->ply.object, free_sprite);
}
