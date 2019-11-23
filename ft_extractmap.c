/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extractmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:03:06 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/23 21:16:20 by roalvare         ###   ########.fr       */
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
	printf("[ROW] = %s\n", row);
	free(*map);
	*map = tab;
	free(line);
	return (NULL);
}

void	set_player(t_player *ply, int x, int y, char dir)
{
	ply->x = (double)x + 0.5;
	ply->y = (double)y + 0.5;
	if (dir == 'N')
	{
		ply->dirx = ply->x;
		ply->diry = y;
	}
	else if (dir == 'S')
	{
		ply->dirx = ply->x;
		ply->diry = y + 1;
	}
	else if (dir == 'E')
	{
		ply->dirx = x;
		ply->diry = ply->y;
	}
	else if (dir == 'W')
	{
		ply->dirx = x + 1;
		ply->diry = ply->y;
	}
}

char	*analize_map(char **map, t_player *ply)
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
			if (isdir(map[y][x]) && (ply->x != 0))
				return ("Two player in map");
			else if (isdir(map[y][x]))
				set_player(ply, x, y, isdir(map[y][x]));
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
	if ((error = analize_map(game->map.map, &game->ply)))
		return (error);
	return (NULL);
}
