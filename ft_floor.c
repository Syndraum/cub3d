/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:34:58 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 18:42:52 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_casting(t_game *game, t_ray *ray, int x)
{
	int y;

	if (ray->pixel_end < 0)
		y = game->win.height;
	else
		y = ray->pixel_end;
	while (y < game->win.height)
	{
		img_pixel_rgb(&game->win.render, x, y, &game->map->floor);
		y++;
	}
}

void	skybox(t_game *game, t_ray *ray, int x)
{
	int y;

	if (ray->pixel_start < 0)
		y = 0;
	else
		y = 0;
	while (y <= ray->pixel_start)
	{
		img_pixel_rgb(&game->win.render, x, y, &game->map->ceil);
		y++;
	}
}
