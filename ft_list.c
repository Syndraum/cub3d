/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:47:47 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/04 15:49:29 by roalvare         ###   ########.fr       */
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
