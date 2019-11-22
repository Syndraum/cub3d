/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_windows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:47:50 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/22 19:22:29 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_windows	*create_windows(t_windows *win, char *title)
{
	if (!(win->id = mlx_new_window(win->mlx, win->width, win->height, title)))
		return (NULL);
	return (win);
}
