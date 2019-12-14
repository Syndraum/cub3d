/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:14:30 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/14 17:49:24 by roalvare         ###   ########.fr       */
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

void	init_minimap(t_minimap *map, t_game *game)
{
	set_xmp(&map->img, "./assets/minimap.xpm", game->mlx);
	set_rgb(&map->blank, 27, 51, 82);
	set_rgb(&map->wall, 54, 89, -120);
	set_rgb(&map->fill, 74, 124, -68);
	set_rgb(&map->ignore, 0, -1, 0);
	set_rgb(&map->ply, 106, (char)190, 48);
	map->height = game->win.height / 4.5;
	map->delcalage = PADDING_MAP * 2 / map->height;
	map->del.x = (double)map->img.width / map->height;
	map->del.y = (double)map->img.height / map->height;
	map->padding = game->win.height / 40;
	map->pi.x = map->padding;
	map->begin.x = game->ply.x - PADDING_MAP;
	map->end.x = game->ply.x + PADDING_MAP;
	map->end.y = game->ply.y + PADDING_MAP;
	map->crs = map->img.data;
	map->tmp.x = 0;
	map->tmp.y = 0;
}

void	print_ply(t_minimap *map, t_game *game)
{
	int size_p;
	int i;
	int j;

	size_p = game->win.height / 100;
	map->pi.x = map->padding + (map->height / 2) - 3;
	i = 0;
	while (i < size_p)
	{
		j = 0;
		map->pi.y = map->padding + (map->height / 2) - 3;
		while (j < size_p)
		{
			img_pixel_rgb(&game->win.render, map->pi.x, map->pi.y, &map->ply);
			(map->pi.y)++;
			j++;
		}
		i++;
		(map->pi.x)++;
	}
}

void	print_minimap(t_minimap *map, t_game *game)
{
	t_rgb color;

	map->begin.y = game->ply.y - PADDING_MAP;
	map->pi.y = map->padding;
	map->tmp.y = 0;
	while (map->tmp.y < map->img.height)
	{
		map->crs = get_img_pixel(&map->img, (int)map->tmp.x, (int)map->tmp.y);
		if (rgbcmp(map->crs, &map->ignore))
		{
			if (!(is_inmap(game->map.map, &map->begin)))
				color = map->blank;
			else if (game->map.map[(int)map->begin.y][(int)map->begin.x] == '1')
				color = map->wall;
			else
				color = map->fill;
			img_pixel_rgb(&game->win.render, map->pi.x, map->pi.y, &color);
		}
		else if (*(map->crs + 3) == 0)
			img_pixel_cpy(&game->win.render, map->pi.x, map->pi.y, map->crs);
		map->begin.y += map->delcalage;
		map->tmp.y += map->del.y;
		(map->pi.y)++;
	}
}

void	minimap(t_game *game)
{
	t_minimap map;

	init_minimap(&map, game);
	while (map.tmp.x < map.img.width)
	{
		print_minimap(&map, game);
		(map.pi.x)++;
		map.tmp.x += map.del.x;
		map.begin.x += map.delcalage;
	}
	print_ply(&map, game);
}
