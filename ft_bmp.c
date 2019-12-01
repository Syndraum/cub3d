/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:19:35 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/01 18:15:48 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	str_fill_cpy(char *str, unsigned int nbr, int size)
{
	int				i;

	i = 0;
	while (nbr)
	{
		str[i] = nbr % 256;
		i++;
		nbr /= 256;
	}
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
}

static void	ft_fill_put(char *str, unsigned int nbr, int size, int fd)
{
	str_fill_cpy(str, nbr, size);
	ft_putnstr_fd(str, fd, size);
}

static void	img_bmp_put(t_img *img, int fd)
{
	char	tmp[8];
	int		i;

	ft_putstr_fd("BM", fd);
	ft_fill_put(&tmp[0], (54 + (img->height * img->width)), 4, fd);
	ft_fill_put(&tmp[0], 0, 4, fd);
	ft_fill_put(&tmp[0], 54, 4, fd);
	ft_fill_put(&tmp[0], 40, 4, fd);
	ft_fill_put(&tmp[0], img->width, 4, fd);
	ft_fill_put(&tmp[0], img->height, 4, fd);
	ft_fill_put(&tmp[0], 2097153, 4, fd);
	ft_fill_put(&tmp[0], 0, 4, fd);
	ft_fill_put(&tmp[0], img->size_l * img->height, 4, fd);
	ft_fill_put(&tmp[0], 11811, 4, fd);
	ft_fill_put(&tmp[0], 11811, 4, fd);
	ft_fill_put(&tmp[0], 0, 8, fd);
	i = img->height;
	while (--i >= 0)
		ft_putnstr_fd((img->data + (i * img->size_l)), fd, img->size_l);
}

void		sreenshot(t_game *game)
{
	int fd;

	if (0 > (fd = open(NAME_SCREENSHOT, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)))
		exit(EXIT_FAILURE);
	raycasting(game);
	img_bmp_put(&game->win.render, fd);
}
