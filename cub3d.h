/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:50:29 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/23 21:17:46 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/errno.h>
#include "get_next_line.h"
#include "libft/libft.h"

typedef struct	s_img
{
	void		*id;
	void		*mlx;
	int			width;
	int			height;
}				t_img;

typedef struct s_windows
{
	void		*mlx;
	void		*id;
	int			width;
	int			height;
}				t_windows;

typedef struct	s_map
{
	char		**map;
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
	t_img		sprite;
	int			floor;
	int			ceil;
}				t_map;

typedef struct	s_player
{
	double		x;
	double		y;
	double		dirx;
	double		diry;
	double		planx;
	double		plany;
}				t_player;

typedef struct s_rgb
{
	double		red;
	double		green;
	double		bleu;
}				t_rgb;

typedef struct	game
{
	void		*mlx;
	t_windows	win;
	t_map		map;
	t_player	ply;
}				t_game;

t_windows		*create_windows(t_windows *win, char *title);
void			*free_windows(t_windows	*windows);

void 			print_colunm(t_img *windows, int colunm, int color);
void			print_color(t_img *windows, int color);

t_img			*create_img(void *mlx);
void			*set_image(t_img *img, int width, int height);
void			*set_xmp(t_img *img, char *path, void *mlx);
void			*free_img(t_img *img);
void			img_pixel_put(t_img *img, int x, int y, int color);

int				ft_error(int error);
int				key_hook(int keycode, t_game *game);

t_map			*set_map(int fd, t_game *game);
void			*print_error(char *error);
char			*extract_line(char *str, t_game *game);
char			*extract_resolution(char *str, t_game *game);
char			*extract_texture(char *str, t_game *game);
char			*extract_color(char *str, t_map *map, char type);

char			*extract_map(int fd, char *line, t_game *game);

char			str_charset(char *str, char *charset);
char			*strdup_wc(char *str, char c);
int				ft_tablen(char **tab);
int				ft_tabcpy(char **dest, char **src);
char			isdir(char c);

void			init_player(t_player *player);

#endif
