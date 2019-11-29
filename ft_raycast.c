/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 11:10:00 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/29 18:04:53 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera = 2 * x / (double)game->win.width - 1;
	ray->ray.x = game->ply.dir.x + game->ply.plan.x * ray->camera;
	ray->ray.y = game->ply.dir.y + game->ply.plan.y * ray->camera;
	ray->map_x = (int)game->ply.x;
	ray->map_y = (int)game->ply.y;
	ray->delta_d.x = fabs(1 / ray->ray.x);
	ray->delta_d.y = fabs(1 / ray->ray.y);
	if (ray->ray.x < 0)
	{
		ray->step_x = -1;
		ray->side_d.x = (game->ply.x - ray->map_x) * ray->delta_d.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_d.x = (ray->map_x + 1.0 - game->ply.x) * ray->delta_d.x;
	}
	if (ray->ray.y < 0)
	{
		ray->step_y = -1;
		ray->side_d.y = (game->ply.y - ray->map_y) * ray->delta_d.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_d.y = (ray->map_y + 1.0 - game->ply.y) * ray->delta_d.y;
	}
	// printf("ray  = (%f, %f)\n", ray->ray.x, ray->ray.y);
	// printf("map  = (%d, %d)\n", ray->map_x, ray->map_y);
	// printf("delt = (%f, %f)\n", ray->delta_d.x, ray->delta_d.y);
	// printf("step = (%d, %d)\n", ray->step_x, ray->step_y);
	// printf("side = (%f, %f)\n", ray->side_d.x, ray->side_d.y);
	// fflush(stdout);
}

void	exec_dda(t_ray *ray, t_game *game)
{
	char hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_d.x < ray->side_d.y)
		{
			ray->side_d.x += ray->delta_d.x;
			ray->map_x += ray->step_x;
			if (ray->step_x == -1)
				ray->wall = 0;
			else
				ray->wall = 2;
			
			// printf("side_x = %f\n", ray->side_d.x);
		}
		else
		{
			ray->side_d.y += ray->delta_d.y;
			ray->map_y += ray->step_y;
			if (ray->step_y == -1)
				ray->wall = 1;
			else
				ray->wall = 3;
			// printf("side_y = %f\n", ray->side_d.y);
		}
		// printf("map  = (%d, %d)\n", ray->map_x, ray->map_y);
		// fflush(stdout);
		if (game->map.map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (ray->wall % 2)
		ray->len = (ray->map_y - game->ply.y + ( 1 - ray->step_y) / 2) / ray->ray.y;
	else
		ray->len = (ray->map_x - game->ply.x + ( 1 - ray->step_x) / 2) / ray->ray.x;
}

t_img	*get_side_texture(t_map *map, char side)
{
	if (side == 0)
		return (&map->east);
	else if (side == 1)
		return (&map->north);
	else if (side == 2)
		return (&map->west);
	else if (side == 3)
		return (&map->south);
	return (NULL);
}

void	drawray(t_game *game, t_ray *ray, int line)
{
	int i;
	int j;
	int text_x;
	int text_y;
	int d;
	t_img *img;

	i = -1;
	j = ray->pixel_start;
	img = get_side_texture(&game->map, ray->wall);
	while (++i < game->win.height)
	{
		if (i < ray->pixel_start)
			img_pixel_put(&game->win.render, line, i, game->map.ceil);
		else if (i >= ray->pixel_end)
			img_pixel_put(&game->win.render, line, i, game->map.floor);
		else
		{
			d = j * 256 - game->win.height * 128 + ray->line_h * 128;
			text_x = (int)(ray->wall_x * (double)img->width);
			if ((ray->wall % 2) && ray->ray.y < 0)
				text_x = img->width - text_x - 1;
			if (!(ray->wall % 2) && ray->ray.x > 0)
				text_x = img->width - text_x - 1;
			text_y = ((d * (double)img->height) / (double)(ray->line_h)) / 256;
			img_pixel_cpy(&game->win.render, line, i, get_img_pixel(img, text_x, text_y));
			j++;
		}
	}
}

void	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < game->win.width)
	{
		init_ray(&ray, game, x);
		exec_dda(&ray, game);
		ray.line_h = (int)(game->win.height / ray.len);
		ray.pixel_start = -ray.line_h / 2 + game->win.height / 2;
		if (ray.pixel_start < 0)
			ray.pixel_start = 0;
		ray.pixel_end = ray.line_h / 2 + game->win.height / 2;
		if (ray.pixel_end >= game->win.height)
			ray.pixel_end = game->win.height - 1;
		if (ray.wall % 2)
			ray.wall_x = game->ply.x + ray.len * ray.ray.x;
		else
			ray.wall_x = game->ply.y + ray.len * ray.ray.y;
		ray.wall_x -= floor(ray.wall_x);
		// printf("len = %d\ndif = %d\n=======", line_h, ray.pixel_end - ray.pixel_start);
		drawray(game, &ray, x);
	}
}
