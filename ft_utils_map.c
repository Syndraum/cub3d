/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:15:41 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/23 21:16:52 by roalvare         ###   ########.fr       */
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

char	isdir(char c)
{
	if (c == 'N')
		return ('N');
	else if (c == 'S')
		return ('S');
	else if (c == 'W')
		return ('W');
	else if (c == 'E')
		return ('E');
	return (0);
}
