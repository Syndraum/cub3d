/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:23:09 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/20 17:40:34 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_colunm(t_img *img, int colunm, int color)
{
	int	i;

	i = -1;
	while (++i < img->height)
		img_pixel_put(img, colunm, i, color);
}

void	print_color(t_img *img, int color)
{
	int x;

	x = -1;
	while (++x < img->width)
		print_colunm(img, x, color);
}
