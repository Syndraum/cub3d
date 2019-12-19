/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extractmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:03:06 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/19 20:11:10 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	ismapvalide(char *line, t_map *map)
{
	while (*line != 0)
	{
		if (!issprite(*line, map) && 0 == ft_strchr(" 01NSWE", *line))
			return (0);
		line++;
	}
	return (1);
}

static char	*extract_line_map(char *line, t_map *m)
{
	char	***map;
	char	*row;
	char	**tab;

	map = &m->map;
	if (!ismapvalide(line, m))
		return (INVALID_CHAR_MAP);
	if (!(row = strdup_wc(line, ' ')))
		return (strerror(12));
	if (!(tab = ft_calloc(sizeof(char*), (ft_tablen(*map) + 2))))
		return (strerror(12));
	ft_tabcpy(tab, *map);
	tab[ft_tablen(*map)] = row;
	free(*map);
	*map = tab;
	free(line);
	return (NULL);
}

static void	set_player(int x, int y, char dir, t_map *map)
{
	map->pos.x = (double)x + 0.5;
	map->pos.y = (double)y + 0.5;
	map->dir = dir;
	map->map[y][x] = '0';
}

void	set_dira(t_game *game)
{
	char dir;

	dir = game->map->dir;
	game->ply.x = game->map->pos.x;
	game->ply.y = game->map->pos.y;
	if (dir == 'N')
		set_dir(&game->ply, 0, -1);
	else if (dir == 'S')
		set_dir(&game->ply, 0, 1);
	else if (dir == 'E')
		set_dir(&game->ply, 1, 0);
	else if (dir == 'W')
		set_dir(&game->ply, -1, 0);
}

static char	*analize_map(t_map *m)
{
	size_t	len;
	int		x;
	int		y;
	char	**map;

	y = -1;
	map = m->map;
	len = ft_strlen(*map);
	while (map[++y])
	{
		x = 0;
		if (len != ft_strlen(map[y]))
			return (WORNG_LINE_LEN_MAP);
		if (map[y][x] != '1' || map[y][ft_strlen(map[y]) - 1] != '1')
			return (BORDER_MAP_ERROR);
		while (map[y][x])
		{
			if ((y == (ft_tablen(map) - 1) || y == 0) && map[y][x] != '1')
				return (BORDER_MAP_ERROR);
			if (isdir(map[y][x]) && (m->pos.x != 0))
				return (TOO_PLAYER);
			else if (isdir(map[y][x]))
				set_player(x, y, isdir(map[y][x]), m);
			x++;
		}
	}
	return (NULL);
}

char	*extract_map(int fd, char *line, t_map *map)
{
	char *error;

	if (!(map->map = ft_calloc(sizeof(char*), 1)))
		return (strerror(12));
	if ((error = extract_line_map(line, map)))
		return (error);
	while ((map->read = get_next_line(fd, &line)) >= 0 && ft_strncmp(line, "", 1))
	{
		if (NULL != (error = extract_line_map(line, map)))
		{
			free(line);
			return (error);
		}
	}
	free(line);
	if ((error = analize_map(map)))
		return (error);
	return (NULL);
}
