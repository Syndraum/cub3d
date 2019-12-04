/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 11:10:00 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/04 17:02:55 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_side_texture(t_map *map, char side)
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

void	drawray(t_game *game, t_ray *ray, int line)
{
	int		i;
	int		j;
	int		d;
	t_img	*img;
	char	*pixel;

	i = -1;
	j = ray->pixel_start;
	img = get_side_texture(&game->map, ray->wall);
	while (++i < game->win.height)
	{
		if (i < ray->pixel_start)
			img_pixel_rgb(&game->win.render, line, i, &game->map.ceil);
		else if (i >= ray->pixel_end)
			img_pixel_rgb(&game->win.render, line, i, &game->map.floor);
		else
		{
			d = j * 2 - game->win.height + ray->line_h;
			ray->text.x = (int)(ray->wall_x * (double)img->width);
			ray->text.y = ((d * (double)img->height) / (double)ray->line_h) / 2;
			pixel = get_img_pixel(img, ray->text.x, ray->text.y);
			img_pixel_cpy(&game->win.render, line, i, pixel);
			j++;
		}
	}
}

void	set_pixelcord(t_game *game, t_ray *ray)
{
	ray->line_h = (int)(game->win.height / ray->len);
	ray->pixel_start = -ray->line_h / 2 + game->win.height / 2;
	if (ray->pixel_start < 0)
		ray->pixel_start = 0;
	ray->pixel_end = ray->line_h / 2 + game->win.height / 2;
	if (ray->pixel_end >= game->win.height)
		ray->pixel_end = game->win.height - 1;
	if (ray->wall % 2)
		ray->wall_x = game->ply.x + ray->len * ray->ray.x;
	else
		ray->wall_x = game->ply.y + ray->len * ray->ray.y;
	ray->wall_x -= floor(ray->wall_x);
}

void	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = -1;
	game->ply.sprite = NULL;
	while (++x < game->win.width)
	{
		init_ray(&ray, game, x);
		exec_dda(&ray, game);
		set_pixelcord(game, &ray);
		drawray(game, &ray, x);
		floor_casting(game, &ray, x);
		game->ply.z_index[x] = ray.len;
	}
	mlx_put_image_to_window(game->mlx, game->win.id, game->win.render.id, 0, 0);
	put_sprite(game);
	ft_lstclear(&game->ply.sprite, free_sprite);
}
