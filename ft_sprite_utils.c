/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:16:35 by roalvare          #+#    #+#             */
/*   Updated: 2019/12/21 15:33:13 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hud(t_game *game)
{
	(void)game;
}

void	set_textx(t_info *i, t_sprite *sprite)
{
	i->text.x = i->text.x * sprite->img.width / i->sprit_widht;
}

int		get_read(int i)
{
	(void)i;
	return (0);
}
