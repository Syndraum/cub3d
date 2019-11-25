/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extractmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:03:06 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/25 15:45:45 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*extract_line_map(char *line, char ***map)
{
	char	*row;
	char	**tab;

	if (!(str_charset(line, " 012NSWE")))
		return ("Invalid character in map");
	if (!(row = strdup_wc(line, ' ')))
		return (strerror(12));
	if (!(tab = ft_calloc(sizeof(char*), (ft_tablen(*map) + 2))))
		return (strerror(12));
	ft_tabcpy(tab, *map);
	tab[ft_tablen(*map)] = row;
	// printf("[ROW] = %s\n", row);
	free(*map);
	*map = tab;
	free(line);
	return (NULL);
}

void	set_player(t_game *game, int x, int y, char dir)
{
	game->ply.x = (double)x + 0.5;
	game->ply.y = (double)y + 0.5;
	if (dir == 'N')
	{
		game->ply.dirx = 0;
		game->ply.diry = -1;
	}
	else if (dir == 'S')
	{
		game->ply.dirx = 0;
		game->ply.diry = 1;
	}
	else if (dir == 'E')
	{
		game->ply.dirx = -1;
		game->ply.diry = 0;
	}
	else if (dir == 'W')
	{
		game->ply.dirx = 1;
		game->ply.diry = 0;
	}
	game->map.map[y][x] = '0';
}

char	*analize_map(char **map, t_game *game)
{
	size_t	len;
	int		x;
	int		y;

	y = -1;
	len = ft_strlen(*map);
	while (map[++y])
	{
		x = 0;
		if (len != ft_strlen(map[y]))
			return ("Wrong lenght line in map");
		if (map[y][x] != '1' || map[y][ft_strlen(map[y]) - 1] != '1')
			return ("Border map error");
		while (map[y][x])
		{
			if ((y == ft_tablen(map) || y == 0) && map[y][x] != '1')
				return ("Border map error");
			if (isdir(map[y][x]) && (game->ply.x != 0))
				return ("Two player in map");
			else if (isdir(map[y][x]))
				set_player(game, x, y, isdir(map[y][x]));
			x++;
		}
	}
	return (NULL);
}

char	*extract_map(int fd, char *line, t_game *game)
{
	char *error;

	if (!(game->map.map = ft_calloc(sizeof(char*), 1)))
		return (strerror(12));
	init_player(&game->ply);
	if ((error = extract_line_map(line, &game->map.map)))
		return (error);
	while (get_next_line(fd, &line) >= 0 && ft_strncmp(line, "", 1))
		if ((error = extract_line_map(line, &game->map.map)))
			return (error);
	if ((error = analize_map(game->map.map, game)))
		return (error);
	return (NULL);
}
