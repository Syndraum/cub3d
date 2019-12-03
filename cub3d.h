/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:50:29 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/03 14:23:08 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/errno.h>
# include "get_next_line.h"
# include "libft/libft.h"

# define MAX_HEIGHT 1400
# define MAX_WIDHT 2560
# define FOV 0.6
# define MOVE_SPEED 0.08
# define ROT_SPEED 0.07
# define NAME_SCREENSHOT "screenshot.bmp"
# define MAX_NBR_SPRITE 256

typedef enum	e_event
{
	FORWARD = 1,
	BACKWARD,
	LEFT,
	RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHIT,
	ESCAPE
}				t_event;

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_rgb
{
	char		red;
	char		green;
	char		blue;
	char		alpha;
}				t_rgb;

typedef struct	s_ray
{
	double		camera;
	t_vector	ray;
	int			map_x;
	int			map_y;
	t_vector	side_d;
	t_vector	delta_d;
	int			step_x;
	int			step_y;
	double		len;
	int			line_h;
	int			pixel_start;
	int			pixel_end;
	char		wall;
	double		wall_x;
}				t_ray;

typedef struct	s_img
{
	void		*id;
	void		*mlx;
	int			width;
	int			height;
	char		*data;
	int			bpp;
	int			end;
	int			size_l;
}				t_img;

typedef struct	s_sprite
{
	t_vector	pos;
	double		dist;
}				t_sprite;

typedef struct s_windows
{
	void		*mlx;
	void		*id;
	int			width;
	int			height;
	t_img		render;
}				t_windows;

typedef struct	s_map
{
	char		**map;
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
	t_img		sprite;
	t_rgb		floor;
	t_rgb		ceil;
}				t_map;

typedef struct	s_player
{
	double		x;
	double		y;
	t_vector	dir;
	t_vector	plan;
	t_list		*sprite;
	// t_vector	sprite[MAX_NBR_SPRITE + 1];
	// double		sprite_dist[MAX_NBR_SPRITE + 1];
}				t_player;

typedef struct	game
{
	void		*mlx;
	t_windows	win;
	t_map		map;
	t_player	ply;
	char		event[ESCAPE];
}				t_game;

int				loop_hook(t_game *game);

t_windows		*create_windows(t_windows *win, char *title);
void			*free_windows(t_windows	*windows);

void	img_pixel_put(t_img *img, int x, int y, int color);
void 	print_colunm(t_img *windows, int colunm, int color);
void	print_color(t_img *windows, int color);
void	print_line(t_img *img, double beg_x, double beg_y, double end_x, double end_y, int color);
void	print_cross(t_img *img, int x, int y, int size);
void	print_map(t_game *game, int size);

void			*set_image(t_img *img, int width, int height, void *mlx);
void			*set_xmp(t_img *img, char *path, void *mlx);
void			img_pixel_cpy(t_img *img, int x, int y, char *color);
void			img_pixel_rgb(t_img *img, int x, int y, t_rgb *color);
char			*get_img_pixel(t_img *img, int x, int y);

void	img_xpm_put(t_img *img, t_img *xpm, int x, int y);
void	xpm_resize_pit(t_img *img, t_img *xpm, int x, int y, int size);

int				ft_error(int error);
int				free_map(char **tab);
void			*print_error(char *error);

int				exit_hook(t_game *game);
int				key_press_hook(int keycode, t_game *game);
int				key_release_hook(int keycode, t_game *game);
int				event_exec(t_game *game);
int				key_hook(int keycode, t_game *game);

t_map			*set_map(int fd, t_game *game);
char			*is_complete(t_game *game);
void			init_map(t_game *game);
char			*extract_line(char *str, t_game *game);
char			*extract_resolution(char *str, t_game *game);
char			*extract_texture(char *str, t_game *game);
char			*extract_color(char *str, t_rgb *type);

char			*extract_map(int fd, char *line, t_game *game);

char			str_charset(char *str, char *charset);
char			*strdup_wc(char *str, char c);
int				ft_tablen(char **tab);
int				ft_tabcpy(char **dest, char **src);
char			isdir(char c);

void			init_player(t_player *player);
void			set_dir(t_player *player, double x, double y);
void			set_vector(t_vector *vector, double x, double y);
void			rotate_vector(t_vector *vector, double speed);

void			raycasting(t_game *game);

t_list			*new_sprite(double dist, double sprit_x, double sprit_y);
void			free_sprite(void *sprite);
void	print_sprite(t_list *lst);
char			add_vector(t_player *ply, double sprit_x, double sprit_y);
void			init_tabvector(t_player *ply);

void			sreenshot(t_game *game);

#endif
