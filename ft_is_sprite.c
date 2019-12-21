/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 14:08:50 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 14:09:53 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	is_id_forbidden(char id)
{
	if (id == '0' || id == '1' || id == 'N' || id == 'W' ||
	id == 'S' || id == 'E')
		return (1);
	if (!ft_isprint(id))
		return (1);
	return (0);
}

char	issprite(char id, t_map *map)
{
	t_list		*cursor;
	t_sprite	*sprite;

	cursor = map->sprite;
	while (cursor != NULL)
	{
		sprite = (t_sprite*)cursor->content;
		if (sprite->id == id)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

char	issprite_wall(char id, t_map *map)
{
	t_list		*cursor;
	t_sprite	*sprite;

	cursor = map->sprite;
	while (cursor != NULL)
	{
		sprite = (t_sprite*)cursor->content;
		if (sprite->id == id && sprite->collision == 1)
			return (1);
		else if (sprite->id == id && sprite->collision == 0)
			return (0);
		cursor = cursor->next;
	}
	return (0);
}

char	issprite_end(char id, t_map *map)
{
	t_list		*cursor;
	t_sprite	*sprite;

	cursor = map->sprite;
	while (cursor != NULL)
	{
		sprite = (t_sprite*)cursor->content;
		if (sprite->id == id && sprite->collision == 2)
			return (1);
		else if (sprite->id == id && sprite->collision == 0)
			return (0);
		cursor = cursor->next;
	}
	return (0);
}

char	issprite_damage(char id, t_map *map)
{
	t_list		*cursor;
	t_sprite	*sprite;

	cursor = map->sprite;
	while (cursor != NULL)
	{
		sprite = (t_sprite*)cursor->content;
		if (sprite->id == id && sprite->effect != 0)
			return (1);
		else if (sprite->id == id && sprite->effect == 0)
			return (0);
		cursor = cursor->next;
	}
	return (0);
}
