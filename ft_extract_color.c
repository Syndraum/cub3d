/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:40:28 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/19 11:37:14 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*extract_sprite(char *str, t_game *game)
{
	char		*cursor;
	t_list		*elmt;
	t_sprite	*sprite;

	if (game->map.sprite != NULL)
		return (DUPLICATE_TEXTURE);
	if (!(elmt = new_sprite()))
		return (ALLOC_FAIL);
	sprite = (t_sprite*)elmt->content;
	cursor = str + 1;
	while (*cursor == ' ')
		cursor++;
	if (!(set_xmp(&sprite->img, cursor, game->mlx)))
	{
		ft_lstdelone(elmt, free_sprite);
		return (strerror(2));
	}
	ft_lstadd_back(&game->map.sprite, elmt);
	return (NULL);
}

char	*extract_color(char *str, t_game *game, char *as_color)
{
	char		*cursor;
	int			value;
	t_rgb		*rgb;

	if (!(ft_strncmp(str, "F", 1)))
		rgb = &game->map.floor;
	else
		rgb = &game->map.ceil;
	cursor = str + 1;
	while (*cursor == ' ')
		cursor++;
	if (!isnumber(*cursor) || (255 < (value = ft_atoi(cursor))))
		return (BAD_RED_FORMAT);
	rgb->red = value;
	while (isnumber(*cursor))
		cursor++;
	if (*cursor == ',')
		cursor++;
	if (!isnumber(*cursor) || 255 < (value = ft_atoi(cursor)))
		return (BAD_GREEN_FORMAT);
	rgb->green = value;
	while (isnumber(*cursor))
		cursor++;
	if (*cursor == ',')
		cursor++;
	if (!isnumber(*cursor) || 255 < (value = ft_atoi(cursor)))
		return (BAD_BLUE_FORMAT);
	rgb->blue = value;
	*as_color = 1;
	return (NULL);
}
