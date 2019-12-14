/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:56:26 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/14 10:28:41 by roalvare         ###   ########.fr       */
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

int		free_game(t_game *game)
{
	free_map(game->map.map);
	free(game->ply.z_index);
	ft_lstclear(&game->ply.sprite, free_sprite);
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
