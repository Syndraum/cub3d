/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:24:55 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/22 19:09:09 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_image(t_img *img)
{
	if (img->id != NULL)
	{
		mlx_destroy_image(img->mlx, img->id);
		img->id = NULL;
	}
}

void	free_maps(void *content)
{
	t_map *map;

	map = (t_map*)content;
	free_map(map->map);
	free_image(&map->north);
	free_image(&map->south);
	free_image(&map->east);
	free_image(&map->west);
	free_image(&map->floor_text);
	free_image(&map->skybox);
	ft_lstclear(&map->sprite, free_sprite);
	free(map);
}

int		free_game(t_game *game)
{
	free(game->ply.z_index);
	free_image(&game->minimap.img);
	free_image(&game->jauge.jauge);
	free_image(&game->jauge.life);
	ft_lstclear(&game->ply.object, free_sprite);
	ft_lstclear(&game->lst_maps, free_maps);
	if (game->win.id != NULL)
	{
		mlx_clear_window(game->mlx, game->win.id);
		mlx_destroy_window(game->mlx, game->win.id);
	}
	return (0);
}

int		free_map(char **tab)
{
	char **cursor;

	cursor = tab;
	if (tab != NULL)
	{
		while (*cursor)
		{
			free(*cursor);
			cursor++;
		}
		free(tab);
	}
	return (0);
}
