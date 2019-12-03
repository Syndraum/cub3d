/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 18:11:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/03 16:46:16 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*new_sprite(double dist, double sprit_x, double sprit_y)
{
	t_list		*elmt;
	t_sprite	*sprite;

	if (!(sprite = ft_calloc(sizeof(t_sprite), 1)))
		return (NULL);
	sprite->pos.x = sprit_x;
	sprite->pos.y = sprit_y;
	sprite->dist = dist;
	if (!(elmt = ft_lstnew(sprite)))
	{
		free(sprite);
		return (NULL);
	}
	return (elmt);
}

t_list	*ft_lstadd(t_list **list, t_list *elmt)
{
	if (list != NULL && elmt != NULL)
	{
		elmt->next = (*list)->next;
		(*list)->next = elmt;
	}
	return (*list);
}

void	free_sprite(void *sprite)
{
	free(sprite);
}

void	print_sprite(t_list *lst)
{
	t_sprite *sprite;
	while (lst != NULL)
	{
		sprite = (t_sprite*)lst->content;
		printf("(%.1f, %.1f | %f) => ", sprite->pos.x, sprite->pos.y, sprite->dist);
		lst = lst->next;
	}
	printf("NULL\n");
}

char	add_vector(t_player *ply, double sprit_x, double sprit_y)
{
	t_list		*cursor;
	t_list		*prec;
	t_sprite	*sprite;
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

// char	add_vector(t_player *ply, double sprit_x, double sprit_y)
// {
// 	int i;

// 	i = -1;
// 	while (ply->sprite[++i].x != -1)
// 		if (ply->sprite[i].x == sprit_x && ply->sprite[i].y == sprit_y)
// 			return (0);
// 	if (i > MAX_NBR_SPRITE)
// 		return (0);
// 	ply->sprite[i].x = sprit_x;
// 	ply->sprite[i].y = sprit_y;
// 	ply->sprite_dist[i] = (pow(ply->x - sprit_x, 2) + pow(ply->y - sprit_y, 2));
// 	ply->sprite[i + 1].x = -1.0;
// 	ply->sprite_dist[i + 1] = -1.0;
// 	// printf("sprite(%.1f, %.1f) %f\n", sprit_x, sprit_y, ply->sprite_dist[i]);
// 	return (1);
// }

void	init_tabvector(t_player *ply)
{
	ply->sprite = NULL;
	// ply->sprite[0].x = -1.0;
	// ply->sprite_dist[0] = -1.0;
}

void	put_sprite(t_game *game)
{
	t_list *lst;
	t_sprite *sprite;
	t_vector sprit_pos;
	double inv_det;
	t_vector trans;
	int sprit_screenx;
	int sprit_height;
	int sprit_widht;
	int draw_starty;
	int draw_endy;
	int draw_startx;
	int draw_endx;
	int textx;
	int texty;

	lst = game->ply.sprite;
	while (lst != NULL)
	{
		sprite = (t_sprite*)lst->content;
		printf("(%f, %f) %f => ", sprite->pos.x, sprite->pos.y, sprite->dist);
		sprit_pos.x = sprite->pos.x - game->ply.x;
		sprit_pos.y = sprite->pos.y - game->ply.y;
		inv_det =  1.0 / (game->ply.plan.x * game->ply.dir.y - game->ply.dir.x * game->ply.plan.y);
		trans.x = inv_det * (game->ply.dir.y * sprit_pos.x - game->ply.dir.x * sprit_pos.y);
		trans.y = inv_det * (-game->ply.plan.y * sprit_pos.x + game->ply.plan.x * sprit_pos.y);
		sprit_screenx = (int)((game->win.width / 2) * (1 + trans.x / trans.y));

		sprit_height = abs((int)((double)game->win.height / (trans.y)));
		draw_starty = -sprit_height / 2 + game->win.height / 2;
		if (draw_starty < 0)
			draw_starty = 0;
		draw_endy = sprit_height / 2 + game->win.height / 2;
		if (draw_endy >= game->win.height)
			draw_endy = game->win.height - 1;

		sprit_widht = abs((int)((double)game->win.height / (trans.y)));
		draw_startx = -sprit_widht / 2 + sprit_screenx;
		if (draw_startx < 0)
			draw_startx = 0;
		draw_endx = sprit_height / 2 + sprit_screenx;
		if (draw_endx >= game->win.width)
			draw_endx = game->win.width - 1;
		int i = draw_startx;
		while (i < draw_endx)
		{
			textx = (int)(256 * (i - (-sprit_widht / 2 + sprit_screenx)) * game->map.sprite.width / sprit_widht) / 256;
			if (i > 0 && i < game->win.width && trans.y < game->ply.z_index[i])
			{
				int y = draw_starty;
				while (y < draw_endy)
				{
					int d = (y) * 256 - game->win.height * 128 + sprit_height * 128;
					texty = ((d * game->map.sprite.height) / sprit_height / 256);
					char *pixel = get_img_pixel(&game->map.sprite, textx, texty);
					if (*(pixel+4) != 0)
						img_pixel_cpy(&game->win.render, i, y, pixel);
					y++;
				}
			}
			i++;
		}
		lst = lst->next;
	}
}
