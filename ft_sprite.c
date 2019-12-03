/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 18:11:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/03 14:26:21 by roalvare         ###   ########.fr       */
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
