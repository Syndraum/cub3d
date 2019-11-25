/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:23:09 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/25 11:33:30 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_colunm(t_img *img, int colunm, int color)
{
	int	i;

	i = -1;
	while (++i < img->height)
		img_pixel_put(img, colunm, i, color);
}

void	print_color(t_img *img, int color)
{
	int x;

	x = -1;
	while (++x < img->width)
		print_colunm(img, x, color);
}

void	print_map(t_game *game, int size)
{
	int x;
	int y;

	y = -1;
	while (game->map.map[++y])
	{
		x = -1;
		while (game->map.map[y][++x])
		{
			if (game->map.map[y][x] == '1')
				xpm_resize_pit(&game->win.render, &game->map.north, x * size, y * size, size);
			else if (game->map.map[y][x] == '0')
				xpm_resize_pit(&game->win.render, &game->map.east, x * size, y * size, size);
			else if (game->map.map[y][x] == '2')
				xpm_resize_pit(&game->win.render, &game->map.west, x * size, y * size, size);
		}
	}
	mlx_put_image_to_window(game->mlx, game->win.id, game->win.render.id, 0, 0);
	xpm_resize_pit(&game->win.render, &game->map.sprite, (game->ply.x-0.5) * size, (game->ply.y-0.5) * size, size);
}

void	print_player(t_game *game, int size_m)
{
	xpm_resize_pit(&game->win.render, &game->map.sprite, game->ply.x * size_m, game->ply.y * size_m, size_m);
}