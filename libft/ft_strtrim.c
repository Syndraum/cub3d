/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:28:20 by roalvare          #+#    #+#             */
/*   Updated: 2019/10/29 23:21:17 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *s2)
{
	char			*begin;
	char			*end;
	char			*trim;
	unsigned int	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	begin = (char*)s1;
	end = (char*)s1 + ft_strlen(s1);
	trim = NULL;
	len = 0;
	while (*begin && ft_strchr(s2, *begin))
		begin++;
	if (*begin)
	{
		while (ft_strrchr(s2, *end))
			end--;
	}
	len = end - begin + 1;
	if (!(trim = ft_calloc(len + 1, sizeof(char))))
		return (trim);
	ft_strlcpy(trim, begin, len + 1);
	return (trim);
}
