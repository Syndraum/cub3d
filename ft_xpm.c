/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xpm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:46:07 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/01 18:47:54 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_xpm_put(t_img *img, t_img *xpm, int x, int y)
{
	int i;
	int j;

	i = -1;
	while (++i < xpm->width)
	{
		j = -1;
		while (++j < xpm->height)
			img_pixel_cpy(img, x + i, y + j, get_img_pixel(xpm, i, j));
	}
}

void	xpm_resize_pit(t_img *img, t_img *xpm, int x, int y, int size)
{
	double	ratio;
	int		i;
	int		j;

	ratio = (double)xpm->width / (double)size;

	i = -1;
	while (++i * ratio < xpm->width)
	{
		j = -1;
		while (++j * ratio < xpm->height)
			img_pixel_cpy(img, x + i, y + j, get_img_pixel(xpm, i * ratio, j * ratio));
	}
}
