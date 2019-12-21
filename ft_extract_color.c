/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:40:28 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 19:32:43 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*extract_sprite(char *str, t_game *game, t_map *map)
{
	char		*cursor;
	t_list		*elmt;
	t_sprite	*sprite;

	if (map->sprite != NULL)
		return (DUPLICATE_TEXTURE);
	if (!(elmt = new_sprite()))
		return (ALLOC_FAIL);
	sprite = (t_sprite*)elmt->content;
	cursor = str + 1;
	strmv_wh(&cursor, ' ');
	if (!(set_xmp(&sprite->img, cursor, game->mlx)))
	{
		ft_lstdelone(elmt, free_sprite);
		return (strerror(2));
	}
	ft_lstadd_back(&map->sprite, elmt);
	return (NULL);
}

char	*extract_color(char *str, t_game *game, char *as_color, t_map *map)
{
	char		*cursor;
	int			value;
	t_rgb		*rgb;

	(void)game;
	if (*as_color == 1)
		return (DUPLICATE_COLOR);
	rgb = (!(ft_strncmp(str, "F", 1))) ? &map->floor : &map->ceil;
	cursor = str + 1;
	strmv_wh(&cursor, ' ');
	if (!isnumber(*cursor) || (255 < (value = ft_atoi(cursor))))
		return (BAD_RED_FORMAT);
	rgb->red = value;
	strmv_ft(&cursor, isnumber);
	strmv_if(&cursor, ',');
	if (!isnumber(*cursor) || 255 < (value = ft_atoi(cursor)))
		return (BAD_GRE_FORMAT);
	rgb->green = value;
	strmv_ft(&cursor, isnumber);
	strmv_if(&cursor, ',');
	if (!isnumber(*cursor) || 255 < (value = ft_atoi(cursor)))
		return (BAD_BLUE_FORMAT);
	rgb->blue = value;
	*as_color = 1;
	return (NULL);
}
