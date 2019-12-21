/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:14:18 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 17:07:30 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strmv_wh(char **line, char c)
{
	while (**line == c)
		(*line)++;
}

void	strmv_if(char **line, char c)
{
	if (**line == c)
		(*line)++;
}
