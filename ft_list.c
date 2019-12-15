/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:47:47 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/15 15:07:07 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*new_object(double dist, double sprit_x, double sprit_y, char id)
{
	t_list		*elmt;
	t_object	*object;

	if (!(object = ft_calloc(sizeof(t_object), 1)))
		return (NULL);
	object->pos.x = sprit_x;
	object->pos.y = sprit_y;
	object->dist = dist;
	object->id = id;
	if (!(elmt = ft_lstnew(object)))
	{
		free(object);
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
