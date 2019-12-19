/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:56:26 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/19 12:49:01 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_error(int error)
{
	if (error == -1)
		perror("");
	else if (error <= 102)
		ft_putendl_fd(strerror(error), 2);
	return (EXIT_FAILURE);
}

void	*print_error(char *error)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error, 2);
	return (NULL);
}

void	free_image(void *mlx, t_img *img)
{
	if (img->id != NULL)
		mlx_destroy_image(mlx, img->id);
}

int		free_game(t_game *game)
{
	free_map(game->map.map);
	free(game->ply.z_index);
	free_image(game->mlx, &game->win.render);
	free_image(game->mlx, &game->map.north);
	free_image(game->mlx, &game->map.south);
	free_image(game->mlx, &game->map.east);
	free_image(game->mlx, &game->map.west);
	free_image(game->mlx, &game->map.floor_text);
	free_image(game->mlx, &game->map.skybox);
	free_image(game->mlx, &game->map.skybox);
	free_image(game->mlx, &game->minimap.img);
	free_image(game->mlx, &game->jauge.jauge);
	free_image(game->mlx, &game->jauge.life);
	ft_lstclear(&game->ply.object, free_sprite);
	ft_lstclear(&game->map.sprite, free_sprite);
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
