/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:09:57 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/20 17:39:31 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*create_img(void *mlx, int width, int height)
{
	t_img	*img;

	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	if (!(img->id = mlx_new_image(mlx, width, height)))
		return (free_img(img));
	img->mlx = mlx;
	img->width = width;
	img->height = height;
	return (img);
}

void	*free_img(t_img *img)
{
	free(img->id);
	free(img);
	return (NULL);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char			*begin;
	int				bpp;
	int				size_l;
	int				endian;
	unsigned int	u_color;

	u_color = mlx_get_color_value(img->mlx, color);
	begin = mlx_get_data_addr(img->id, &bpp, &size_l, &endian);
	begin += (y * size_l) + (x * bpp / (sizeof(char) * 8));
	*begin = u_color;
	*(begin + 1) = u_color / 256;
	*(begin + 2) = u_color / 256 / 256;
}
