/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:43:32 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/19 11:19:00 by roalvare         ###   ########.fr       */
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
		rsl = extract_color(str, game, &game->map.as_floor);
	else if (ft_strnstr(str, "C", 1) == str)
		rsl = extract_color(str, game, &game->map.as_ceil);
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

char	*extract_texture(char *str, t_game *game)
{
	char	*cursor;
	t_img	*img;

	if (!(ft_strncmp(str, "NO", 2)))
		img = &game->map.north;
	else if (!(ft_strncmp(str, "SO", 2)))
		img = &game->map.south;
	else if (!(ft_strncmp(str, "WE", 2)))
		img = &game->map.west;
	else
		img = &game->map.east;
	if (img->id != NULL)
		return ("Duplicate texture");
	cursor = str + 2;
	while (*cursor == ' ')
		cursor++;
	if (!(set_xmp(img, cursor, game->mlx)))
		return (strerror(2));
	return (NULL);
}
