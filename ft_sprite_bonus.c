/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:35:59 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/22 13:33:24 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		*verif_id(t_sprite *sprite, char **cursor, t_map *map)
{
	if (is_id_forbidden(**cursor))
		return (SPRITE_FORBIDDEN_ID);
	if (issprite(**cursor, map))
		return (SPRITE_ID_BE_UNIQUE);
	sprite->id = **(cursor);
	(*cursor)++;
	if (**cursor != ' ')
		return (SPRITE_ID_NOT_FOUND);
	strmv_wh(cursor, ' ');
	return (NULL);
}

static char		*verif_collision(t_sprite *sprite, char **cursor)
{
	if (**cursor == '1')
		sprite->collision = 1;
	else if (**cursor == '0')
		sprite->collision = 0;
	else if (**cursor == '2')
		sprite->collision = 2;
	else
		return (BAD_COLLISION);
	(*cursor)++;
	if (**cursor != ' ')
		return (COLLISION_NOT_FOUND);
	strmv_wh(cursor, ' ');
	return (NULL);
}

static char		*verif_effect(t_sprite *sprite, char **cursor)
{
	if (!ft_isdigit(**cursor) && **cursor != '-')
		return (BAD_EFFECT);
	sprite->effect = ft_atoi(*cursor);
	while (ft_isdigit(**cursor) || **cursor == '-')
		(*cursor)++;
	if (**cursor != ' ')
		return (EFFECT_NOT_FOUND);
	strmv_wh(cursor, ' ');
	return (NULL);
}

static	char	*error_free(char *str, t_list *elmt)
{
	ft_lstdelone(elmt, free_sprite);
	return (str);
}

char			*extract_sprite(char *str, t_game *game, t_map *map)
{
	char		*cursor;
	char		*error;
	t_list		*elmt;
	t_sprite	*sprite;

	if (!(elmt = new_sprite()))
		return (ALLOC_FAIL);
	sprite = (t_sprite*)elmt->content;
	cursor = str + 1;
	strmv_wh(&cursor, ' ');
	if (NULL != (error = verif_id(sprite, &cursor, map)))
		return (error_free(error, elmt));
	if (NULL != (error = verif_collision(sprite, &cursor)))
		return (error_free(error, elmt));
	if (NULL != (error = verif_effect(sprite, &cursor)))
		return (error_free(error, elmt));
	if (!(set_xmp(&sprite->img, cursor, game->mlx)))
		return (error_free(strerror(2), elmt));
	ft_lstadd_back(&map->sprite, elmt);
	return (NULL);
}
