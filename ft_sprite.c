/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 18:11:39 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 15:33:04 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list		*new_sprite(void)
{
	t_list		*elmt;
	t_sprite	*sprite;

	if (!(sprite = ft_calloc(1, sizeof(t_sprite))))
		return (NULL);
	sprite->id = '2';
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

t_sprite	*get_sprite(char *id, t_game *game)
{
	t_list		*cursor;
	t_sprite	*sprite;

	cursor = game->map->sprite;
	while (cursor != NULL)
	{
		sprite = (t_sprite*)cursor->content;
		if (sprite->id == *id)
			return (sprite);
		cursor = cursor->next;
	}
	return (NULL);
}

void		add_step_sprite(t_list *lst)
{
	t_sprite	*sprite;
	t_list		*cursor;

	cursor = lst;
	while (cursor != NULL)
	{
		sprite = (t_sprite*)cursor->content;
		sprite->step = (sprite->step + sprite->img.height) % sprite->img.width;
		cursor = cursor->next;
	}
}
