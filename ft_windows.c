/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_windows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:47:50 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/22 15:20:37 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_windows	*create_windows(t_windows *win, char *title)
{
	if (!(win->id = mlx_new_window(win->link_id, win->width, win->height, title)))
		return (free_windows(win));
	return (win);
}

void		*free_windows(t_windows *windows)
{
	free(windows);
	return (NULL);
}
