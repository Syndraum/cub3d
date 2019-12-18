/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:43:32 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/18 12:30:00 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*set_map(int fd, t_game *game)
{
	char	*line;
	char	*error;
	char	finish;

	finish = 0;
	error = NULL;
	init_map(game);
	while (get_next_line(fd, &line) == 1 && !finish)
	{
		if (ft_strnstr(line, "1", 1) == line)
		{
			if ((error = extract_map(fd, line, game)))
				return (print_error(error));
			finish = 1;
		}
		else if ((error = extract_line(line, game)))
			return (print_error(error));
	}
	free(line);
	if ((error = is_complete(game)))
		return (print_error(error));
	return (&game->map);
}

char	*is_complete(t_game *game)
{
	if (game->map.map == NULL)
		return ("Map is missing");
	else if (game->map.north.id == NULL)
		return ("North texture is missing");
	else if (game->map.south.id == NULL)
		return ("South texture is missing");
	else if (game->map.east.id == NULL)
		return ("East texture is missing");
	else if (game->map.west.id == NULL)
		return ("West texture is missing");
	else if (game->map.sprite == NULL)
		return ("Sprite texture is missing");
	else if (game->win.height == 0 || game->win.width == 0)
		return ("Definition is missing");
	else if (game->map.as_ceil == 0)
		return ("ceil color is missing");
	else if (game->map.as_floor == 0)
		return ("floor color is missing");
	return (NULL);
}

void	init_rgb(t_rgb *rgb)
{
	rgb->alpha = 0;
	rgb->blue = 0;
	rgb->green = 0;
	rgb->red = 0;
}

void	init_map(t_game *game)
{
	game->win.height = 0;
	game->win.width = 0;
	game->map.map = NULL;
	game->map.north.id = NULL;
	game->map.south.id = NULL;
	game->map.east.id = NULL;
	game->map.west.id = NULL;
	game->map.sprite = NULL;
	// game->map.sprite.img.id = NULL;
	// game->map.sprite.step = 0;
	game->map.floor_text.id = NULL;
	game->map.skybox.id = NULL;
	init_rgb(&game->map.ceil);
	init_rgb(&game->map.floor);
	game->map.as_ceil = 0;
	game->map.as_floor = 0;
}

char	*extract_line(char *str, t_game *game)
{
	static char *rsl = "A line is not empty";

	if (ft_strnstr(str, "R", 1) == str)
		rsl = extract_resolution(str, game);
	else if (ft_strnstr(str, "NO", 2) == str)
		rsl = extract_texture(str, game);
	else if (ft_strnstr(str, "SO", 2) == str)
		rsl = extract_texture(str, game);
	else if (ft_strnstr(str, "WE", 2) == str)
		rsl = extract_texture(str, game);
	else if (ft_strnstr(str, "EA", 2) == str)
		rsl = extract_texture(str, game);
	else if (ft_strnstr(str, "S", 1) == str)
		rsl = extract_sprite(str, game);
	else if (ft_strnstr(str, "F", 1) == str)
	{
		if (BONUS && NULL == (rsl = extract_texture(str, game)))
			game->map.as_floor = 1;
		else if (!BONUS)
			rsl = extract_color(str, &game->map.floor, &game->map.as_floor);
	}
	else if (ft_strnstr(str, "C", 1) == str)
	{
		if (BONUS && NULL == (rsl = extract_texture(str, game)))
			game->map.as_ceil = 1;
		else if (!BONUS)
			rsl = extract_color(str, &game->map.ceil, &game->map.as_ceil);
	}
	else if (ft_strnstr(str, "", 1) == str)
		rsl = NULL;
	free(str);
	return (rsl);
}

char	*extract_resolution(char *str, t_game *game)
{
	char	*cursor;

	cursor = str + 1;
	while (*cursor == ' ')
		cursor++;
	if (game->win.width != 0)
		return ("Duplicate resolution");
	if (0 >= (game->win.width = ft_atoi(cursor)))
		return ("Wrong widht, resolution need to be higher than 0 x 0");
	if (game->win.width > MAX_WIDHT)
		game->win.width = MAX_WIDHT;
	while (isnumber(*cursor))
		cursor++;
	while (*cursor == ' ')
		cursor++;
	if (0 >= (game->win.height = ft_atoi(cursor)))
		return ("Wrong height, resolution need to be higher than 0 x 0");
	if (game->win.height > MAX_HEIGHT)
		game->win.height = MAX_HEIGHT;
	return (NULL);
}

char	*extract_sprite(char *str, t_game *game)
{
	char		*cursor;
	t_list		*elmt;
	t_sprite	*sprite;

	if (!BONUS && game->map.sprite != NULL)
		return ("Duplicate sprite");
	if (!(elmt = new_sprite()))
		return ("Allocution failed");
	sprite = (t_sprite*)elmt->content;
	cursor = str + 1;
	while (*cursor == ' ')
		cursor++;
	if (BONUS)
	{
		if (is_id_forbidden(*cursor))
			return ("Forbiddent identifiant");
		if (issprite(*cursor, game))
			return ("Identifiant be unique");
		sprite->id = *(cursor++);
		if (*cursor != ' ')
			return ("Srite identifiant not found");
		while (*cursor == ' ')
			cursor++;
		if (*cursor == '1')
			sprite->collision = 1;
		else if (*cursor == '0')
			sprite->collision = 0;
		else
			return ("Bad collision setting");
		cursor++;
		if (*cursor != ' ')
			return ("Collision setting not found");
		while (*cursor == ' ')
			cursor++;
		if (!ft_isdigit(*cursor) && *cursor != '-')
			return ("Effect setting not found");
		sprite->effect = ft_atoi(cursor);
		while (ft_isdigit(*cursor) || *cursor == '-')
			cursor++;
		if (*cursor != ' ')
			return ("Bad effect setting");
		while (*cursor == ' ')
			cursor++;
	}
	if (!(set_xmp(&sprite->img, cursor, game->mlx)))
	{
		ft_lstdelone(elmt, free_sprite);
		return (strerror(2));
	}
	ft_lstadd_back(&game->map.sprite, elmt);
	return (NULL);
}

char	*extract_texture(char *str, t_game *game)
{
	char	*cursor;
	t_img	*img;
	char	s_prefix;

	s_prefix = 2;
	if (!(ft_strncmp(str, "NO", 2)))
		img = &game->map.north;
	else if (!(ft_strncmp(str, "SO", 2)))
		img = &game->map.south;
	else if (!(ft_strncmp(str, "WE", 2)))
		img = &game->map.west;
	else if (!(ft_strncmp(str, "EA", 2)))
		img = &game->map.east;
	else
	{
		if (!(ft_strncmp(str, "F", 1)))
			img = &game->map.floor_text;
		else
			img = &game->map.skybox;
		s_prefix = 1;
	}
	if (img->id != NULL)
		return ("Duplicate texture");
	cursor = str + s_prefix;
	while (*cursor == ' ')
		cursor++;
	if (!(set_xmp(img, cursor, game->mlx)))
		return (strerror(2));
	return (NULL);
}

char	*extract_color(char *str, t_rgb *type, char *as_color)
{
	char		*cursor;
	int			value;

	cursor = str + 1;
	while (*cursor == ' ')
		cursor++;
	if (!isnumber(*cursor) || (255 < (value = ft_atoi(cursor))))
		return ("Bad red format, colors need to be between 0 and 255");
	type->red = value;
	while (isnumber(*cursor))
		cursor++;
	if (*cursor == ',')
		cursor++;
	if (!isnumber(*cursor) || 255 < (value = ft_atoi(cursor)))
		return ("Bad green format, colors need to be between 0 and 255");
	type->green = value;
	while (isnumber(*cursor))
		cursor++;
	if (*cursor == ',')
		cursor++;
	if (!isnumber(*cursor) || 255 < (value = ft_atoi(cursor)))
		return ("Bad green format, colors need to be between 0 and 255");
	type->blue = value;
	*as_color = 1;
	return (NULL);
}
