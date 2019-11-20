/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_windows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:47:50 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/20 17:48:46 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_windows	*create_windows(void *link_id, int width, int height, char *title)
{
	t_windows	*windows;

	if (!(windows = malloc(sizeof(t_windows))))
		return (NULL);
	if (!(windows->id = mlx_new_window(link_id, width, height, title)))
		return (free_windows(windows));
	windows->width = width;
	windows->height = height;
	windows->link_id = link_id;
	return (windows);
}

void		*free_windows(t_windows *windows)
{
	free(windows);
	return (NULL);
}
