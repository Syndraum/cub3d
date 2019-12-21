/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 14:04:45 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 14:05:17 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*init_lstmap(void)
{
	t_list	*elmt;
	t_map	*map;

	elmt = NULL;
	if (!(map = ft_calloc(1, sizeof(t_map))))
		return (NULL);
	if (!(elmt = ft_lstnew(map)))
	{
		free(map);
		return (NULL);
	}
	init_map(map);
	return (elmt);
}

void	init_rgb(t_rgb *rgb)
{
	rgb->alpha = 0;
	rgb->blue = 0;
	rgb->green = 0;
	rgb->red = 0;
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->north.id = NULL;
	map->south.id = NULL;
	map->east.id = NULL;
	map->west.id = NULL;
	map->sprite = NULL;
	map->floor_text.id = NULL;
	map->skybox.id = NULL;
	init_rgb(&map->ceil);
	init_rgb(&map->floor);
	map->as_ceil = 0;
	map->as_floor = 0;
}
