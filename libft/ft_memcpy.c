/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:37:34 by roalvare          #+#    #+#             */
/*   Updated: 2019/10/19 16:08:02 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*src_cpy;
	unsigned char		*dst_cpy;

	if (dst == src)
		return (dst);
	src_cpy = src;
	dst_cpy = dst;
	while (n-- > 0)
	{
		*dst_cpy = *src_cpy;
		dst_cpy++;
		src_cpy++;
	}
	return (dst);
}
