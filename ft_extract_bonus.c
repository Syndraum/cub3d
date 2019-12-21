/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:45:08 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 16:38:59 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_read(int i)
{
	return (i);
}

char	*extract_color(char *str, t_game *game, char *as_color, t_map *map)
{
	char	*cursor;
	t_img	*img;

	if (!(ft_strncmp(str, "F", 1)))
		img = &map->floor_text;
	else
		img = &map->skybox;
	if (img->id != NULL)
		return (DUPLICATE_TEXTURE);
	cursor = str + 2;
	strmv_wh(&cursor, ' ');
	if (!(set_xmp(img, cursor, game->mlx)))
		return (strerror(2));
	*as_color = 1;
	return (NULL);
}
