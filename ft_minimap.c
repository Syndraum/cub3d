/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:14:30 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/07 21:24:08 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	is_inmap(char **map, t_vector *vector)
{
	if (vector->x < 0 || vector->y < 0)
		return (0);
	if (vector->x > ft_strlen(map[0]))
		return (0);
	if (vector->y > ft_tablen(map))
		return (0);
	return (1);
}

char	rgbcmp(char *cursor, t_rgb *rgb)
{
	if (rgb->red != *(cursor + 2))
		return (0);
	else if (rgb->green != *(cursor + 1))
		return (0);
	else if (rgb->blue != *cursor)
		return (0);
	return (1);
}

void	set_rgb(t_rgb *rgb, char red, char green, char blue)
{
	rgb->red = red;
	rgb->green = green;
	rgb->blue = blue;
	rgb->alpha = 0;
}

void	minimap(t_game *game)
{
	t_img img;
	set_xmp(&img, "./assets/minimap.xpm", game->mlx);
	t_vector begin;
	t_vector end;
	t_rgb	wall;
	t_rgb	blank;
	t_rgb	fill;
	t_rgb	ignore;
	t_coord	pixel;

	double height = 150;
	double delcalage = PADDING_MAP * 2 / height;
	double del_x = (double)img.width / (double)height;
	double del_y = (double)img.height / (double)height;
	double x = 0;
	double y = 0;

	pixel.x = 10;
	pixel.y = 10;
	set_rgb(&blank, 37, 38, 41);
	set_rgb(&wall, 89, 86, 82);
	set_rgb(&fill, 113, 114, 117);
	set_rgb(&ignore, 30, (char)153, 72);
	begin.x = game->ply.x - PADDING_MAP;
	end.x = game->ply.x + PADDING_MAP;
	end.y = game->ply.y + PADDING_MAP;

	char *cursor = img.data;
	while (x < img.width)
	{
		begin.y = game->ply.y - PADDING_MAP;
		pixel.y = 10;
		y = 0;
		while (y < img.height)
		{
			cursor = get_img_pixel(&img, (int)x, (int)y);
			if (rgbcmp(cursor , &ignore))
			{
				if (!(is_inmap(game->map.map, &begin)))
					img_pixel_rgb(&game->win.render, pixel.x, pixel.y, &blank);
				else if (game->map.map[(int)begin.y][(int)begin.x] == '1')
					img_pixel_rgb(&game->win.render, pixel.x, pixel.y, &wall);
				else
					img_pixel_rgb(&game->win.render, pixel.x, pixel.y, &fill);
			}
			else if (*(cursor + 3) == 0)
				img_pixel_cpy(&game->win.render, pixel.x, pixel.y, cursor);
			begin.y += delcalage;
			y += del_y;
			(pixel.y)++;
		}
		(pixel.x)++;
		x += del_x;
		begin.x += delcalage;
		// cursor += 4;
	}
	pixel.x = 10 + (height / 2) - 3;
	int i = 0;
	int j;
	t_rgb ply;
	set_rgb(&ply, 106, (char)190, 48);
	while (i < 6)
	{
		j = 0;
		pixel.y = 10 + (height / 2) - 3;
		while (j < 6)
		{
			img_pixel_rgb(&game->win.render, pixel.x, pixel.y, &ply);
			(pixel.y)++;
			j++;
		}
		i++;
		(pixel.x)++;
	}
}
