/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:50:29 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/19 20:15:13 by roalvare         ###   ########.fr       */
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
# define ROT_SPEED 0.045
# define NAME_SCREENSHOT "screenshot.bmp"
# define MAX_NBR_SPRITE 256
# define PADDING_MAP 6
# define PLY_LIFE 100.0

# define ALLOC_FAIL "Allocution failed"
# define LINE_NOT_EMPTY "A line is not empty"

# define DUPLICATE_DEFINITION "Duplicate definition"
# define WRONG_WIDHT "Wrong widht, definition need to be higher than 0 x 0"
# define WRONG_HEIGHT "Wrong height, definition need to be higher than 0 x 0"
# define MISSING_DEFINITON "Definition is missing"

# define BAD_RED_FORMAT "Bad red format, colors need to be between 0 and 255"
# define BAD_GREEN_FORMAT "Bad green format, colors need to be between 0 and 255"
# define BAD_BLUE_FORMAT "Bad blue format, colors need to be between 0 and 255"
# define CEIL_MISSING "Ceil is missing"
# define FLOOR_MISSING "Floor is missing"

# define INVALID_CHAR_MAP "Invalid character in map"
# define BORDER_MAP_ERROR "Map need to be surrounded by character '1'"
# define WORNG_LINE_LEN_MAP "Wromg lines lenght in map"
# define TOO_PLAYER	"Two or more players in map"
# define MAP_MISSING "Map is missing"

# define DUPLICATE_TEXTURE "Duplicate texture"
# define NO_TEXT_MISSING "North texture is missing"
# define SO_TEXT_MISSING "South texture is missing"
# define EA_TEXT_MISSING "East texture is missing"
# define WE_TEXT_MISSING "West texture is missing"
# define SRITE_MISSING "Sprite texture is missing"
# define SPRITE_FORBIDDEN_ID "Forbiddent identifiant"
# define SPRITE_ID_BE_UNIQUE "Identifiant be unique"
# define SPRITE_ID_NOT_FOUND "Srite identifiant not found"
# define BAD_COLLISION "Bad collision setting"
# define COLLISION_NOT_FOUND "Collision setting not found"
# define BAD_EFFECT "Bad effect setting"
# define EFFECT_NOT_FOUND "Effect setting not found"

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

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

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
	t_coord		map;
	t_vector	side_d;
	t_vector	delta_d;
	t_coord		step;
	double		len;
	int			line_h;
	int			pixel_start;
	int			pixel_end;
	char		wall;
	double		wall_x;
	t_coord		text;
	double 		angle;
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
	t_img		img;
	int 		step;
	char		id;
	char		collision;
	int			effect;
}				t_sprite;

typedef struct	s_object
{
	t_vector	pos;
	double		dist;
	char		id;
}				t_object;

typedef struct s_info
{
	t_vector	tmp;
	double		det;
	t_vector	trans;
	int			sprit_screenx;
	int			sprit_height;
	int			sprit_widht;
	t_coord		draw_start;
	t_coord		draw_end;
	t_coord		text;
}				t_info;

typedef struct	s_minimap
{
	t_img		img;
	t_rgb		wall;
	t_rgb		blank;
	t_rgb		fill;
	t_rgb		ignore;
	t_rgb		ply;
	t_vector	tmp;
	t_vector	begin;
	t_vector	end;
	t_vector	del;
	t_coord		pi;
	double		height;
	double		delcalage;
	int			padding;
	char		*crs;
}				t_minimap;

typedef struct	s_jauge
{
	t_img		jauge;
	t_img		life;
	t_vector	tmp;
	t_vector	del;
	t_coord		pi;
	double		height;
	double		widht;
	char		*crs_j;
	char		*crs_l;
}				t_jauge;

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
	t_list		*sprite;
	char		as_floor;
	t_img		floor_text;
	t_rgb		floor;
	char		as_ceil;
	t_img		skybox;
	t_rgb		ceil;
	int			read;
	t_vector	pos;
	char		dir;		
}				t_map;

typedef struct	s_player
{
	double		life;
	double		x;
	double		y;
	t_vector	dir;
	t_vector	plan;
	t_list		*object;
	double		*z_index;
}				t_player;

typedef struct	game
{
	void		*mlx;
	t_windows	win;
	t_list		*lst_maps;
	t_map		*map;
	t_player	ply;
	t_minimap	minimap;
	t_jauge		jauge;
	char		event[ESCAPE];
}				t_game;

int				loop_hook(t_game *game);

t_windows		*create_windows(t_windows *win, char *title);

void			*set_image(t_img *img, int width, int height, void *mlx);
void			*set_xmp(t_img *img, char *path, void *mlx);
void			img_pixel_cpy(t_img *img, int x, int y, char *color);
void			img_pixel_rgb(t_img *img, int x, int y, t_rgb *color);
char			*get_img_pixel(t_img *img, int x, int y);

void			img_xpm_put(t_img *img, t_img *xpm, int x, int y);

int				ft_error(int error);
int				free_game(t_game *game);
void			free_maps(void *content);
int				free_map(char **tab);
int				print_error(char *error);

int				exit_hook(t_game *game);
int				key_press_hook(int keycode, t_game *game);
int				key_release_hook(int keycode, t_game *game);
int				event_exec(t_game *game);
int				key_hook(int keycode, t_game *game);

int				set_map(int fd, t_game *game);
char			*is_complete(t_game *game, t_map *map);
void			init_map(t_map *map);
char			*extract_line(char *str, t_game *game, t_map *map);
char			*extract_resolution(char *str, t_game *game);
char			*extract_texture(char *str, t_game *game, t_map *map);

void			set_dira(t_game *game);
char			*extract_map(int fd, char *line, t_map *map);

char			str_charset(char *str, char *charset);
char			*strdup_wc(char *str, char c);
int				ft_tablen(char **tab);
int				ft_tabcpy(char **dest, char **src);
char			isdir(char c);

void			init_player(t_player *player);
void			set_dir(t_player *player, double x, double y);
void			set_vector(t_vector *vector, double x, double y);
void			rotate_vector(t_vector *vector, double speed);

void			init_ray(t_ray *ray, t_game *game, int x);
void			exec_dda(t_ray *ray, t_game *g);
void			raycasting(t_game *game);
void			floor_casting(t_game *game, t_ray *ray, int x);

t_list			*new_object(double dist, double sprit_x, double sprit_y, char id);
t_list			*ft_lstadd(t_list **list, t_list *elmt);
void			free_sprite(void *sprite);

t_list			*new_sprite(void);
t_sprite		*get_sprite(char *id, t_game *game);
char			issprite(char id, t_map *map);
char			issprite_end(char id, t_map *map);
char			issprite_wall(char id, t_map *map);
char			issprite_damage(char id, t_map *map);
char			is_id_forbidden(char id);
char			add_vector(t_player *ply, double x, double y, char id);
void			print_sprite(t_game *game, t_info *info, t_sprite *sprite);
void			put_sprite(t_game *game);

void			sreenshot(t_game *game);

void			hud(t_game *game);
void			init_minimap(t_minimap *map, t_game *game);
void			init_jauge(t_jauge *jauge, t_minimap *map, t_game *game);

void			skybox(t_game *game, t_ray *ray, int x);

void			damage(t_game *game, int damage);

void			move(t_game *game, double move_x, double move_y);

char			*extract_color(char *str, t_game *game, char *as_color, t_map *map);
char			*extract_sprite(char *str, t_game *game, t_map *map);

void			set_textx(t_info *i, t_sprite *sprite);

#endif
