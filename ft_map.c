/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:43:32 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/22 14:59:10 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*set_map(int fd, t_game *game)
{
	char	*line;
	char	ext;

	game->map->north = create_img(game->win->link_id); //
	game->map->south = create_img(game->win->link_id); //
	game->map->east = create_img(game->win->link_id); //
	game->map->west = create_img(game->win->link_id); //
	game->map->sprite = create_img(game->win->link_id); //
	while (get_next_line(fd, &line) == 1)
	{
		if (1 != (ext = extract_line(line, game)))
		{
			ft_putendl_fd("Error", 2);
			ft_putendl_fd(line, 2);
			ft_error(-1);
			if (ext == -1)
				ft_putendl_fd("Wrong resolution format", 2);
			else if (ext == -2)
				ft_putendl_fd("North texture not found", 2);
			free(line);
			return (NULL);
		}
		free(line);
	}
	printf("[WIDTH] = %d\n[HEIGHT] = %d\n", game->map->north->width, game->map->north->height);
	return (game->map);
}

char	extract_line(char *str, t_game *game)
{
	int rsl;

	rsl = 1;
	if (ft_strnstr(str, "R", 1) == str)
		rsl = extract_resolution(str, game);
	else if (ft_strnstr(str, "NO", 2) == str)
		rsl = extract_texture(str, game->map->north, "NO");
	else if (ft_strnstr(str, "SO", 2) == str)
		rsl = extract_texture(str, game->map->south, "SO");
	else if (ft_strnstr(str, "WE", 2) == str)
		rsl = extract_texture(str, game->map->west, "WE");
	else if (ft_strnstr(str, "EA", 2) == str)
		rsl = extract_texture(str, game->map->east, "EA");
	else if (ft_strnstr(str, "S", 1) == str)
		rsl = extract_texture(str, game->map->sprite, "S");
	return (rsl);
}

char	extract_resolution(char *str, t_game *game)
{
	char	*cursor;

	cursor = str + 1;
	while (*cursor == ' ')
		cursor++;
	if (isnumber(*cursor))
		game->win->width = ft_atoi(cursor);
	else
		return (0);
	while (isnumber(*cursor))
		cursor++;
	while (*cursor == ' ')
		cursor++;
	if (isnumber(*cursor))
		game->win->height = ft_atoi(cursor);
	else
		return (0);
	return (1);
}

int		extract_texture(char *str, t_img *img, char *type)
{
	char	*cursor;

	cursor = str + ft_strlen(type);
	while (*cursor == ' ')
		cursor++;
	if (!(set_xmp(img, cursor)))
		return (0);
	return (1);
}

void	*free_map(t_map *map)
{
	while (*map->map != NULL)
	{
		free(*map->map);
		(map->map)++;
	}
	// free(map->north);
	// free(map->south);
	// free(map->west);
	// free(map->east);
	// free(map->sprite);
	free(map);
	return (NULL);
}
