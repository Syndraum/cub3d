/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:14:30 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/19 18:00:39 by roalvare         ###   ########.fr       */
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

void		init_minimap(t_minimap *map, t_game *game)
{
	set_rgb(&map->blank, 27, 51, 82);
	set_rgb(&map->wall, 54, 89, -120);
	set_rgb(&map->fill, 74, 124, -68);
	set_rgb(&map->ignore, 0, -1, 0);
	set_rgb(&map->ply, 106, -65, 48);
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

static void	print_ply(t_minimap *map, t_game *game)
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

static void	print_minimap(t_minimap *map, t_game *game)
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
			if (!(is_inmap(game->map->map, &map->begin)))
				color = map->blank;
			else if (game->map->map[(int)map->begin.y][(int)map->begin.x] == '1')
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

void	init_jauge(t_jauge *jauge, t_minimap *map, t_game *game)
{
	jauge->height = game->win.height / 25;
	jauge->widht = game->win.width / 3.5;
	jauge->del.x = (double)jauge->jauge.width / jauge->widht;
	jauge->del.y = (double)jauge->jauge.height / jauge->height;
	jauge->crs_j = jauge->jauge.data;
	jauge->crs_l = jauge->jauge.data;
	jauge->pi.x = map->height + 2 * map->padding;
	jauge->tmp.x = 0;
	jauge->tmp.y = 0;
}

void	print_jauge(t_jauge *j, t_minimap *map, t_game *game)
{
	while (j->tmp.x < j->jauge.width)
	{
		j->pi.y = 2 * map->padding;
		j->tmp.y = 0;
		while (j->tmp.y < j->jauge.height)
		{
			j->crs_j = get_img_pixel(&j->jauge, (int)j->tmp.x, (int)j->tmp.y);
			j->crs_l = get_img_pixel(&j->life, (int)j->tmp.x, (int)j->tmp.y);
			if (*(j->crs_l + 3) == 0 &&
			100 * j->tmp.x / j->jauge.width < game->ply.life)
				img_pixel_cpy(&game->win.render, j->pi.x, j->pi.y, j->crs_l);
			else if (*(j->crs_j + 3) == 0)
				img_pixel_cpy(&game->win.render, j->pi.x, j->pi.y, j->crs_j);
			j->tmp.y += j->del.y;
			(j->pi.y)++;
		}
		(j->pi.x)++;
		j->tmp.x += j->del.x;
	}
}

void		hud(t_game *game)
{
	init_minimap(&game->minimap, game);
	while (game->minimap.tmp.x < game->minimap.img.width)
	{
		print_minimap(&game->minimap, game);
		(game->minimap.pi.x)++;
		game->minimap.tmp.x += game->minimap.del.x;
		game->minimap.begin.x += game->minimap.delcalage;
	}
	print_ply(&game->minimap, game);
	init_jauge(&game->jauge, &game->minimap, game);
	print_jauge(&game->jauge, &game->minimap, game);
}
