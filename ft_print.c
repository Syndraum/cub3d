/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:23:09 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/25 17:42:58 by roalvare         ###   ########.fr       */
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

void	print_line(t_img *img, double beg_x, double beg_y, double end_x, double end_y, int color)
{
	double diff_x = end_x - beg_x;
	double diff_y = end_y - beg_y;
	double del_x;
	double del_y;
	double max = (fabs(diff_x) > fabs(diff_y)) ? fabs(diff_x) : fabs(diff_y);
	if (fabs(diff_x) > fabs(diff_y))
	{
		if (diff_x > 0)
			del_x = 1;
		else
			del_x = -1;
		if (diff_x == 0)
			del_y = 0;
		else
			del_y = diff_y / diff_x;
	}
	else
	{
		if (diff_y > 0)
			del_y = 1;
		else
			del_y = -1;
		if (diff_y == 0)
			del_x = 0;
		else
			del_x = diff_x / diff_y;
	}
	double i = 0;
	while (i < max)
	{
		img_pixel_put(img, (int)beg_x, (int)beg_y, color);
		beg_x += del_x;
		beg_y += del_y;
		i++;
	}
}

void	print_cross(t_img *img, int x, int y, int size)
{
	int i = -size;

	while (i < size + 1)
	{
		img_pixel_put(img, x + i, y, 0xFF0000);
		img_pixel_put(img, x, y + i, 0xFF0000);
		i++;
	}
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
				xpm_resize_pit(&game->win.render, &game->map.west, x * size, y * size, size);
			else if (game->map.map[y][x] == '2')
				xpm_resize_pit(&game->win.render, &game->map.east, x * size, y * size, size);
		}
	}
	// printf("dirx = %.0f\tdiry = %.0f\n", game->ply.dirx, game->ply.diry);
	double dirx = (game->ply.x * size) + (game->ply.dir.x * size);
	double diry = (game->ply.y * size) + (game->ply.dir.y * size);
	double planex = game->ply.plan.x * size;
	double planey = game->ply.plan.y * size;
	print_cross(&game->win.render, game->ply.x * size, game->ply.y * size, 10);
	print_line(&game->win.render, game->ply.x * size, game->ply.y * size, dirx - planex, diry - planey, 0xFF0000);
	print_line(&game->win.render, game->ply.x * size, game->ply.y * size, dirx + planex, diry + planey, 0xFF0000);
	print_line(&game->win.render, game->ply.x * size, game->ply.y * size, dirx, diry, 0xFF00);
	print_line(&game->win.render, dirx - planex, diry - planey, dirx + planex, diry + planey, 0xFF);
	// print_line(&game->win.render, dirx, diry, dirx - planex, diry - planey, 0xFF);
	mlx_put_image_to_window(game->mlx, game->win.id, game->win.render.id, 0, 0);
}
