/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:53:00 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/04 15:53:45 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_side(t_ray *ray, t_game *game)
{
	if (ray->ray.x < 0)
	{
		ray->step.x = -1;
		ray->side_d.x = (game->ply.x - ray->map.x) * ray->delta_d.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_d.x = (ray->map.x + 1.0 - game->ply.x) * ray->delta_d.x;
	}
	if (ray->ray.y < 0)
	{
		ray->step.y = -1;
		ray->side_d.y = (game->ply.y - ray->map.y) * ray->delta_d.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_d.y = (ray->map.y + 1.0 - game->ply.y) * ray->delta_d.y;
	}
}

void		init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera = 2 * x / (double)game->win.width - 1;
	ray->ray.x = game->ply.dir.x + game->ply.plan.x * ray->camera;
	ray->ray.y = game->ply.dir.y + game->ply.plan.y * ray->camera;
	ray->map.x = (int)game->ply.x;
	ray->map.y = (int)game->ply.y;
	ray->delta_d.x = fabs(1 / ray->ray.x);
	ray->delta_d.y = fabs(1 / ray->ray.y);
	init_side(ray, game);
}

static void	ray_increment(t_ray *ray)
{
	if (ray->side_d.x < ray->side_d.y)
	{
		ray->side_d.x += ray->delta_d.x;
		ray->map.x += ray->step.x;
		if (ray->step.x == -1)
			ray->wall = 0;
		else
			ray->wall = 2;
	}
	else
	{
		ray->side_d.y += ray->delta_d.y;
		ray->map.y += ray->step.y;
		if (ray->step.y == -1)
			ray->wall = 1;
		else
			ray->wall = 3;
	}
}

void		exec_dda(t_ray *ray, t_game *g)
{
	char		hit;
	t_vector	sprite;

	hit = 0;
	while (hit == 0)
	{
		ray_increment(ray);
		if (g->map.map[ray->map.y][ray->map.x] == '2')
		{
			sprite.x = (double)(ray->map.x) + 0.5;
			sprite.y = (double)(ray->map.y) + 0.5;
			add_vector(&g->ply, sprite.x, sprite.y);
		}
		else if (g->map.map[ray->map.y][ray->map.x] == '1')
			hit = 1;
	}
	if (ray->wall % 2)
		ray->len = (ray->map.y - g->ply.y + (1 - ray->step.y) / 2) / ray->ray.y;
	else
		ray->len = (ray->map.x - g->ply.x + (1 - ray->step.x) / 2) / ray->ray.x;
}
