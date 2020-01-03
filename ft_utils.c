/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:14:18 by roalvare          #+#    #+#             */
/*   Updated: 2020/01/03 20:07:50 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		strmv_wh(char **line, char c)
{
	while (**line == c)
		(*line)++;
}

void		strmv_if(char **line, char c)
{
	if (**line == c)
		(*line)++;
}

void		strmv_ft(char **line, int (*f)(int))
{
	while (f(**line))
		(*line)++;
}

static char	is_cub(const char *filename)
{
	const char *cursor;

	if (filename == NULL)
		return (0);
	if (ft_strlen(filename) < 4)
		return (0);
	cursor = filename + (ft_strlen(filename) - 4);
	if (ft_strncmp(cursor, ".cub", 4))
		return (0);
	return (1);
}

int			get_file(const char *filename)
{
	int fd;

	if (!is_cub(filename))
		return (ft_error(103));
	if (0 > (fd = open(filename, O_RDONLY)))
		return (ft_error(-1));
	return (fd);
}
