/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:17:06 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/23 12:26:37 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_textx(t_info *i, t_sprite *sprite)
{
	i->text.x = i->text.x * sprite->img.height / i->widht;
	i->text.x += sprite->step;
}
