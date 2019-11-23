/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extractmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:03:06 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/23 15:30:31 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	str_charset(char *str, char *charset)
{
	int i;

	i = -1;
	while (str[++i])
		if (!(ft_strchr(charset, str[i])))
			return (0);
	return (1);
}

char	*strdup_wc(char *str, char c)
{
	int		count;
	int		i;
	char	*dup;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] != c)
			count++;
	if (!(dup = ft_calloc(sizeof(char), count + 1)))
		return (NULL);
	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] != c)
			dup[count++] = str[i];
	return (dup);
}

int		ft_tablen(char **tab)
{
	int	count;

	count = 0;
	if (tab == NULL)
		return (-1);
	while (tab[count])
		count++;
	return (count);
}

int		ft_tabcpy(char **dest, char **src)
{
	int i;

	if (dest == NULL || src == NULL)
		return (0);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	return (i);
}

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

char	*extract_map(int fd, char *line, t_game *game)
{
	char *error;

	if (!(game->map.map = ft_calloc(sizeof(char*), 1)))
		return (strerror(12));
	game->ply.x = 0;
	game->ply.y = 0;
	if ((error = extract_line_map(line, &game->map.map)))
		return (error);
	while (get_next_line(fd, &line) >= 0 && ft_strncmp(line, "", 1))
		if ((error = extract_line_map(line, &game->map.map)))
			return (error);
	return (NULL);
}
