/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 18:11:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/15 13:26:35 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*get_sprite(void)
{
	t_list		*elmt;
	t_sprite	*sprite;

	if (!(sprite = ft_calloc(1, sizeof(t_sprite))))
		return (NULL);
	sprite->id = 0;
	sprite->img.id = NULL;
	sprite->step = 0;
	sprite->collision = 0;
	sprite->effect = 0;
	if (!(elmt = ft_lstnew(sprite)))
	{
		free(sprite);
		return (NULL);
	}
	return (elmt);
}

char	issprite(char id, t_game *game)
{
	t_list		*cursor;
	t_sprite	*sprite;

	cursor = game->map.sprite;
	while (cursor != NULL)
	{
		sprite = (t_sprite*)cursor->content;
		if (sprite->id == id)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

char	add_vector(t_player *ply, double sprit_x, double sprit_y)
{
	t_list		*cursor;
	t_list		*prec;
	t_lstsprite	*sprite;
	double		dist;

	dist = (pow(ply->x - sprit_x, 2) + pow(ply->y - sprit_y, 2));
	cursor = ply->sprite;
	prec = NULL;
	while (cursor != NULL)
	{
		sprite = cursor->content;
		if (sprit_x == sprite->pos.x && sprit_y == sprite->pos.y)
			return (0);
		if (sprite->dist < dist)
			break ;
		prec = cursor;
		cursor = cursor->next;
	}
	if (prec == NULL)
		ft_lstadd_front(&ply->sprite, new_sprite(dist, sprit_x, sprit_y));
	else
		ft_lstadd(&prec, new_sprite(dist, sprit_x, sprit_y));
	return (1);
}

void	print_sprite(t_game *g, t_info *i, t_sprite *sprite)
{
	int		x;
	int		y;
	int		d;
	char	*pixel;

	x = i->draw_start.x;
	while (x < i->draw_end.x)
	{
		i->text.x = (x - (-i->sprit_widht / 2 + i->sprit_screenx));
		if (BONUS)
		{
			i->text.x = i->text.x * sprite->img.height / i->sprit_widht;
			i->text.x += sprite->step;
		}
		else
			i->text.x = i->text.x * sprite->img.width / i->sprit_widht;
		if (x > 0 && x < g->win.width && i->trans.y < g->ply.z_index[x])
		{
			y = i->draw_start.y;
			while (y < i->draw_end.y)
			{
				d = (y) * 2 - g->win.height + i->sprit_height;
				i->text.y = ((d * sprite->img.height) / i->sprit_height / 2);
				pixel = get_img_pixel(&sprite->img, i->text.x, i->text.y);
				if (*(pixel + 4) != 0)
					img_pixel_cpy(&g->win.render, x, y, pixel);
				y++;
			}
		}
		x++;
	}
}

void	set_info(t_player *ply, t_windows *w, t_info *i, t_lstsprite *sprite)
{
	i->tmp.x = sprite->pos.x - ply->x;
	i->tmp.y = sprite->pos.y - ply->y;
	i->det = 1.0 / (ply->plan.x * ply->dir.y - ply->dir.x * ply->plan.y);
	i->trans.x = i->det * (ply->dir.y * i->tmp.x - ply->dir.x * i->tmp.y);
	i->trans.y = i->det * (-ply->plan.y * i->tmp.x + ply->plan.x * i->tmp.y);
	i->sprit_screenx = (int)((w->width / 2) * (1 + i->trans.x / i->trans.y));
}

void	put_sprite(t_game *game)
{
	t_list		*lst;
	t_info		info;

	lst = game->ply.sprite;
	while (lst != NULL)
	{
		set_info(&game->ply, &game->win, &info, (t_lstsprite*)lst->content);
		info.sprit_height = abs((int)(game->win.height / (info.trans.y)));
		info.draw_start.y = -info.sprit_height / 2 + game->win.height / 2;
		if (info.draw_start.y < 0)
			info.draw_start.y = 0;
		info.draw_end.y = info.sprit_height / 2 + game->win.height / 2;
		if (info.draw_end.y >= game->win.height)
			info.draw_end.y = game->win.height - 1;
		info.sprit_widht = abs((int)(game->win.height / (info.trans.y)));
		info.draw_start.x = -info.sprit_widht / 2 + info.sprit_screenx;
		if (info.draw_start.x < 0)
			info.draw_start.x = 0;
		info.draw_end.x = info.sprit_height / 2 + info.sprit_screenx;
		if (info.draw_end.x >= game->win.width)
			info.draw_end.x = game->win.width - 1;
		print_sprite(game, &info, game->map.sprite->content);
		lst = lst->next;
	}
}
