/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:45:08 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/19 11:21:03 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*extract_sprite(char *str, t_game *game)
{
	char		*cursor;
	t_list		*elmt;
	t_sprite	*sprite;

	if (!(elmt = new_sprite()))
		return ("Allocution failed");
	sprite = (t_sprite*)elmt->content;
	cursor = str + 1;
	while (*cursor == ' ')
		cursor++;
	if (is_id_forbidden(*cursor))
		return ("Forbiddent identifiant");
	if (issprite(*cursor, game))
		return ("Identifiant be unique");
	sprite->id = *(cursor++);
	if (*cursor != ' ')
		return ("Srite identifiant not found");
	while (*cursor == ' ')
		cursor++;
	if (*cursor == '1')
		sprite->collision = 1;
	else if (*cursor == '0')
		sprite->collision = 0;
	else
		return ("Bad collision setting");
	cursor++;
	if (*cursor != ' ')
		return ("Collision setting not found");
	while (*cursor == ' ')
		cursor++;
	if (!ft_isdigit(*cursor) && *cursor != '-')
		return ("Effect setting not found");
	sprite->effect = ft_atoi(cursor);
	while (ft_isdigit(*cursor) || *cursor == '-')
		cursor++;
	if (*cursor != ' ')
		return ("Bad effect setting");
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
	char	*cursor;
	t_img	*img;

	if (!(ft_strncmp(str, "F", 1)))
		img = &game->map.floor_text;
	else
		img = &game->map.skybox;
	if (img->id != NULL)
		return ("Duplicate texture");
	cursor = str + 2;
	while (*cursor == ' ')
		cursor++;
	if (!(set_xmp(img, cursor, game->mlx)))
		return (strerror(2));
	*as_color = 1;
	return (NULL);
}
