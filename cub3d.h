/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:50:29 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/20 17:01:28 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct s_windows
{
	void		*link_id;
	void		*id;
	int			width;
	int			height;
}				t_windows;

typedef struct s_img
{
	void		*id;
	int			width;
	int			height;
}				t_img;

typedef struct s_rgb
{
	double		red;
	double		green;
	double		bleu;
}				t_rgb;

t_windows		*create_windows(void *init, int width, int height, char *title);
void			*free_windows(t_windows	*windows);

int				key_hook(int keycode, void *param);

void			img_pixel_put(t_img *img, int x, int y, unsigned int color);
void 			print_colunm(t_img *windows, void *mlx, int colunm, int color);
void			print_color(t_img *windows, void *mlx, int color);

void	print_line(t_windows *windows, void *img, int line, int color);

void	print_gradiant(t_windows *windows, int color1, int color2, int begin, int end);

#endif
