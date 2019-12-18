/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:17:06 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/18 18:27:30 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_sprite(t_sprite *sprite)
{
	sprite->id = 0;
}

void	set_textx(t_info *i, t_sprite *sprite)
{
	i->text.x = i->text.x * sprite->img.height / i->sprit_widht;
	i->text.x += sprite->step;
}
