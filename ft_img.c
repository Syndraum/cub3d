/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:09:57 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/01 18:50:23 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*set_image(t_img *img, int width, int height, void *mlx)
{
	if (!(img->id = mlx_new_image(mlx, width, height)))
		return (NULL);
	img->width = width;
	img->height = height;
	img->data = mlx_get_data_addr(img->id, &img->bpp, &img->size_l, &img->end);
	return (img);
}

void	*set_xmp(t_img *img, char *path, void *mlx)
{
	img->mlx = mlx;
	img->id = mlx_xpm_file_to_image(img->mlx, path, &img->width, &img->height);
	if (img->id == NULL)
		return (NULL);
	img->data = mlx_get_data_addr(img->id, &img->bpp, &img->size_l, &img->end);
	return (img);
}

void	img_pixel_cpy(t_img *img, int x, int y, char *color)
{
	char	*cursor;

	cursor = img->data;
	cursor += (y * img->size_l) + (x * img->bpp / (sizeof(char) * 8));
	cursor[0] = color[0];
	cursor[1] = color[1];
	cursor[2] = color[2];
	cursor[3] = color[3];
}

void	img_pixel_rgb(t_img *img, int x, int y, t_rgb *color)
{
	char	*cursor;

	cursor = img->data;
	cursor += (y * img->size_l) + (x * img->bpp / (sizeof(char) * 8));
	cursor[2] = color->red;
	cursor[1] = color->green;
	cursor[0] = color->blue;
	cursor[3] = color->alpha;
}

char	*get_img_pixel(t_img *img, int x, int y)
{
	char	*cursor;

	cursor = img->data;
	cursor += (y * img->size_l) + (x * img->bpp / (sizeof(char) * 8));
	return (cursor);
}
