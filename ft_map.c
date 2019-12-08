/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:43:32 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/08 10:32:03 by roalvare         ###   ########.fr       */
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
	else if (game->map.sprite.id == NULL)
		return ("Sprite texture is missing");
	else if (game->win.height == 0 || game->win.width == 0)
		return ("Definition is mising");
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
	game->map.sprite.id = NULL;
	game->map.floor_text.id = NULL;
	init_rgb(&game->map.ceil);
	init_rgb(&game->map.floor);
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
		rsl = extract_texture(str, game);
	else if (ft_strnstr(str, "F", 1) == str)
	{
		if (NULL != (rsl = extract_texture(str, game)))
			rsl = extract_color(str, &game->map.floor);
	}
	else if (ft_strnstr(str, "C", 1) == str)
		rsl = extract_color(str, &game->map.ceil);
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
	if (!isnumber(*cursor))
		return ("Wrong widht format");
	game->win.width = ft_atoi(cursor);
	if (game->win.width > MAX_WIDHT)
		game->win.width = MAX_WIDHT;
	while (isnumber(*cursor))
		cursor++;
	while (*cursor == ' ')
		cursor++;
	if (!isnumber(*cursor))
		return ("Wrong height format");
	game->win.height = ft_atoi(cursor);
	if (game->win.height > MAX_HEIGHT)
		game->win.height = MAX_HEIGHT;
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
			img = &game->map.sprite;
		s_prefix = 1;
	}
	cursor = str + s_prefix;
	while (*cursor == ' ')
		cursor++;
	if (!(set_xmp(img, cursor, game->mlx)))
		return (strerror(2));
	return (NULL);
}

char	*extract_color(char *str, t_rgb *type)
{
	char		*cursor;
	int			value;

	cursor = str + 1;
	while (*cursor == ' ')
		cursor++;
	if (!isnumber(*cursor) || (255 < (value = ft_atoi(cursor))))
		return ("Red color wrong format");
	type->red = value;
	while (isnumber(*cursor))
		cursor++;
	if (*cursor == ',')
		cursor++;
	if (!isnumber(*cursor) || 255 < (value = ft_atoi(cursor)))
		return ("Green color wrong format");
	type->green = value;
	while (isnumber(*cursor))
		cursor++;
	if (*cursor == ',')
		cursor++;
	if (!isnumber(*cursor) || 255 < (value = ft_atoi(cursor)))
		return ("Blue color wrong format");
	type->blue = value;
	type->alpha = 0;
	return (NULL);
}
