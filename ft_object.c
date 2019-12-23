/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_object.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 14:11:10 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/23 12:47:27 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	add_vector(t_player *ply, double sprit_x, double sprit_y, char id)
{
	t_list		*cursor;
	t_list		*prec;
	t_object	*object;
	double		dist;

	dist = (pow(ply->x - sprit_x, 2) + pow(ply->y - sprit_y, 2));
	cursor = ply->object;
	prec = NULL;
	while (cursor != NULL)
	{
		object = cursor->content;
		if (sprit_x == object->pos.x && sprit_y == object->pos.y)
			return (0);
		if (object->dist < dist)
			break ;
		prec = cursor;
		cursor = cursor->next;
	}
	if (prec == NULL)
		ft_lstadd_front(&ply->object, new_object(dist, sprit_x, sprit_y, id));
	else
		ft_lstadd(&prec, new_object(dist, sprit_x, sprit_y, id));
	return (1);
}

void	print_sprite(t_game *g, t_info *s, t_sprite *sprite)
{
	int		i;
	int		j;
	int		y;
	char	*pixel;

	i = s->start.x;
	while (i < s->end.x)
	{
		s->text.x = (i - (s->screen_x - s->widht / 2));
		set_textx(s, sprite);
		if (s->rotate.y > 0 && i > 0 && i < g->win.width &&
		s->rotate.y < g->ply.z_wall[i])
		{
			j = s->start.y - 1;
			while (++j < s->end.y)
			{
				y = j * 2 - g->win.height + s->height;
				s->text.y = ((y * sprite->img.height) / s->height / 2);
				pixel = get_img_pixel(&sprite->img, s->text.x, s->text.y);
				if (*(pixel + 3) == 0)
					img_pixel_cpy(&g->win.render, i, j, pixel);
			}
		}
		i++;
	}
}

void	set_info(t_player *ply, t_windows *w, t_info *i, t_object *object)
{
	i->tmp.x = object->pos.x - ply->x;
	i->tmp.y = object->pos.y - ply->y;
	i->det = 1.0 / (ply->plan.x * ply->dir.y - ply->dir.x * ply->plan.y);
	i->rotate.x = i->det * (ply->dir.y * i->tmp.x - ply->dir.x * i->tmp.y);
	i->rotate.y = i->det * (-ply->plan.y * i->tmp.x + ply->plan.x * i->tmp.y);
	i->screen_x = (int)((w->width / 2) * (1 + i->rotate.x / i->rotate.y));
	i->height = abs((int)(w->height / (i->rotate.y)));
	i->widht = abs((int)(w->height / (i->rotate.y)));
}

void	put_sprite(t_game *game)
{
	t_list		*lst;
	t_info		info;
	t_object	*object;

	lst = game->ply.object;
	while (lst != NULL)
	{
		object = (t_object*)lst->content;
		set_info(&game->ply, &game->win, &info, object);
		info.start.y = game->win.height / 2 - info.height / 2;
		if (info.start.y < 0)
			info.start.y = 0;
		info.end.y = game->win.height / 2 + info.height / 2;
		if (info.end.y >= game->win.height)
			info.end.y = game->win.height - 1;
		info.start.x = info.screen_x - info.widht / 2;
		if (info.start.x < 0)
			info.start.x = 0;
		info.end.x = info.screen_x + info.height / 2;
		if (info.end.x >= game->win.width)
			info.end.x = game->win.width - 1;
		print_sprite(game, &info, get_sprite(&object->id, game));
		lst = lst->next;
	}
}
