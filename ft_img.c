/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:09:57 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/23 10:20:34 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*create_img(void *mlx)
{
	t_img	*img;

	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	img->mlx = mlx;
	img->width = 0;
	img->height = 0;
	return (img);
}

void	*set_image(t_img *img, int width, int height)
{
	if (!(img->id = mlx_new_image(img->mlx, width, height)))
		return (NULL);
	img->width = width;
	img->height = height;
	return (img);
}

void	*set_xmp(t_img *img, char *path, void *mlx)
{
	img->mlx = mlx;
	img->id = mlx_xpm_file_to_image(img->mlx, path, &img->width, &img->height);
	if (img->id == NULL)
		return (NULL);
	return (img);
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
