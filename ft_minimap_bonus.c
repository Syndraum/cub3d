/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:14:30 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/23 11:58:39 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		is_inmap(char **map, t_vector *vector)
{
	if (vector->x < 0 || vector->y < 0)
		return (0);
	if (vector->x > ft_strlen(map[0]))
		return (0);
	if (vector->y > ft_tablen(map))
		return (0);
	return (1);
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

static void	print_minimap(t_minimap *m, t_game *game)
{
	t_rgb color;

	m->begin.y = game->ply.y - PADDING_MAP;
	m->pi.y = m->padding;
	m->tmp.y = 0;
	while (m->tmp.y < m->img.height)
	{
		m->crs = get_img_pixel(&m->img, (int)m->tmp.x, (int)m->tmp.y);
		if (rgbcmp(m->crs, &m->ignore))
		{
			if (!(is_inmap(game->map->map, &m->begin)))
				color = m->blank;
			else if (game->map->map[(int)m->begin.y][(int)m->begin.x] == '1')
				color = m->wall;
			else
				color = m->fill;
			img_pixel_rgb(&game->win.render, m->pi.x, m->pi.y, &color);
		}
		else if (*(m->crs + 3) == 0)
			img_pixel_cpy(&game->win.render, m->pi.x, m->pi.y, m->crs);
		m->begin.y += m->delcalage;
		m->tmp.y += m->del.y;
		(m->pi.y)++;
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
