/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:43:32 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/22 19:27:01 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*set_map(int fd, t_game *game)
{
	char	*line;
	char	ext;

	game->map.north.mlx = game->mlx; //
	game->map.south.mlx = game->mlx; //
	game->map.east.mlx = game->mlx; //
	game->map.west.mlx = game->mlx; //
	game->map.sprite.mlx = game->mlx; //
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strnstr(line, "1", 1) == line)
			printf("[MAP]\n");
		else if (1 != (ext = extract_line(line, game)))
		{
			ft_putendl_fd("Error\nMessage a ajouter", 2);
			free(line);
			return (NULL);
		}
		free(line);
	}
	return (&game->map);
}

char	extract_line(char *str, t_game *game)
{
	int rsl;

	rsl = 0;
	if (ft_strnstr(str, "R", 1) == str)
		rsl = extract_resolution(str, game);
	else if (ft_strnstr(str, "NO", 2) == str)
		rsl = extract_texture(str, &game->map.north, "NO");
	else if (ft_strnstr(str, "SO", 2) == str)
		rsl = extract_texture(str, &game->map.south, "SO");
	else if (ft_strnstr(str, "WE", 2) == str)
		rsl = extract_texture(str, &game->map.west, "WE");
	else if (ft_strnstr(str, "EA", 2) == str)
		rsl = extract_texture(str, &game->map.east, "EA");
	else if (ft_strnstr(str, "S", 1) == str)
		rsl = extract_texture(str, &game->map.sprite, "S");
	else if (ft_strnstr(str, "F", 1) == str)
		rsl = extract_color(str, &game->map, 'F');
	else if (ft_strnstr(str, "C", 1) == str)
		rsl = extract_color(str, &game->map, 'C');
	else if (ft_strnstr(str, "", 1) == str)
		rsl = 1;
	return (rsl);
}

char	extract_resolution(char *str, t_game *game)
{
	char	*cursor;

	cursor = str + 1;
	while (*cursor == ' ')
		cursor++;
	if (isnumber(*cursor))
		game->win.width = ft_atoi(cursor);
	else
		return (0);
	while (isnumber(*cursor))
		cursor++;
	while (*cursor == ' ')
		cursor++;
	if (isnumber(*cursor))
		game->win.height = ft_atoi(cursor);
	else
		return (0);
	return (1);
}

char	extract_texture(char *str, t_img *img, char *type)
{
	char	*cursor;

	cursor = str + ft_strlen(type);
	while (*cursor == ' ')
		cursor++;
	if (!(set_xmp(img, cursor)))
		return (0);
	return (1);
}

char	extract_color(char *str, t_map *map, char type)
{
	char			*cursor;
	unsigned char	tab[3];

	cursor = str + 1;
	while (*cursor == ' ')
		cursor++;
	if (!isnumber(*cursor) || 255 < (tab[0] = ft_atoi(cursor)))
		return (0);
	while (isnumber(*cursor))
		cursor++;
	if (*cursor == ',')
		cursor++;
	if (!isnumber(*cursor) || 255 < (tab[1] = ft_atoi(cursor)))
		return (0);
	while (isnumber(*cursor))
		cursor++;
	if (*cursor == ',')
		cursor++;
	if (!isnumber(*cursor) || 255 < (tab[2] = ft_atoi(cursor)))
		return (0);
	if (type == 'F')
		map->floor = tab[2] + (tab[1] * 256) + (tab[0] * 65536);
	else if (type == 'C')
		map->ceil = tab[2] + (tab[1] * 256) + (tab[0] * 65536);
	return (1);
}
