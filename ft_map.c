/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:43:32 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/19 18:44:49 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*set_map(int fd, t_game *game)
{
	t_list	*elmt;
	t_map	*map;
	char	*line;
	char	*error;
	char	finish;

	if (!(map = ft_calloc(1, sizeof(t_map))))
		return (NULL); //
	if (!(elmt = ft_lstnew(map)))
		return (NULL); //
	finish = 0;
	error = NULL;
	init_map(map);
	while (get_next_line(fd, &line) == 1 && !finish)
	{
		if (ft_strnstr(line, "1", 1) == line)
		{
			printf("BEGIN_MAP\n");
			fflush(stdout);
			if ((error = extract_map(fd, line, game, map)))
				return (print_error(error));
			printf("END_MAP\n");
			fflush(stdout);
			finish = 1;
		}
		else if ((error = extract_line(line, game, map)))
			return (print_error(error));
	}
	free(line);
	if ((error = is_complete(game, map)))
		return (print_error(error));
	ft_lstadd_back(&game->lst_maps, elmt);
	game->map = map;
	return (map);
}

char	*is_complete(t_game *game, t_map *map)
{
	if (map->map == NULL)
		return (MAP_MISSING);
	else if (map->north.id == NULL)
		return (NO_TEXT_MISSING);
	else if (map->south.id == NULL)
		return (SO_TEXT_MISSING);
	else if (map->east.id == NULL)
		return (EA_TEXT_MISSING);
	else if (map->west.id == NULL)
		return (WE_TEXT_MISSING);
	else if (map->sprite == NULL)
		return (SRITE_MISSING);
	else if (game->win.height == 0 || game->win.width == 0)
		return (MISSING_DEFINITON);
	else if (map->as_ceil == 0)
		return (CEIL_MISSING);
	else if (map->as_floor == 0)
		return (FLOOR_MISSING);
	return (NULL);
}

void	init_rgb(t_rgb *rgb)
{
	rgb->alpha = 0;
	rgb->blue = 0;
	rgb->green = 0;
	rgb->red = 0;
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->north.id = NULL;
	map->south.id = NULL;
	map->east.id = NULL;
	map->west.id = NULL;
	map->sprite = NULL;
	map->floor_text.id = NULL;
	map->skybox.id = NULL;
	init_rgb(&map->ceil);
	init_rgb(&map->floor);
	map->as_ceil = 0;
	map->as_floor = 0;
}

char	*extract_line(char *str, t_game *game, t_map *map)
{
	static char *rsl = LINE_NOT_EMPTY;

	if (ft_strnstr(str, "R", 1) == str)
		rsl = extract_resolution(str, game);
	else if (ft_strnstr(str, "NO", 2) == str)
		rsl = extract_texture(str, game, map);
	else if (ft_strnstr(str, "SO", 2) == str)
		rsl = extract_texture(str, game, map);
	else if (ft_strnstr(str, "WE", 2) == str)
		rsl = extract_texture(str, game, map);
	else if (ft_strnstr(str, "EA", 2) == str)
		rsl = extract_texture(str, game, map);
	else if (ft_strnstr(str, "S", 1) == str)
		rsl = extract_sprite(str, game, map);
	else if (ft_strnstr(str, "F", 1) == str)
		rsl = extract_color(str, game, &map->as_floor, map);
	else if (ft_strnstr(str, "C", 1) == str)
		rsl = extract_color(str, game, &map->as_ceil, map);
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
		return (DUPLICATE_DEFINITION);
	if (0 >= (game->win.width = ft_atoi(cursor)))
		return (WRONG_WIDHT);
	if (game->win.width > MAX_WIDHT)
		game->win.width = MAX_WIDHT;
	while (isnumber(*cursor))
		cursor++;
	while (*cursor == ' ')
		cursor++;
	if (0 >= (game->win.height = ft_atoi(cursor)))
		return (WRONG_HEIGHT);
	if (game->win.height > MAX_HEIGHT)
		game->win.height = MAX_HEIGHT;
	return (NULL);
}

char	*extract_texture(char *str, t_game *game, t_map *map)
{
	char	*cursor;
	t_img	*img;

	if (!(ft_strncmp(str, "NO", 2)))
		img = &map->north;
	else if (!(ft_strncmp(str, "SO", 2)))
		img = &map->south;
	else if (!(ft_strncmp(str, "WE", 2)))
		img = &map->west;
	else
		img = &map->east;
	if (img->id != NULL)
		return (DUPLICATE_TEXTURE);
	cursor = str + 2;
	while (*cursor == ' ')
		cursor++;
	if (!(set_xmp(img, cursor, game->mlx)))
		return (strerror(2));
	return (NULL);
}
