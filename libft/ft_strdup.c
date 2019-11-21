/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:55:44 by roalvare          #+#    #+#             */
/*   Updated: 2019/11/14 17:19:21 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *copy;

	copy = NULL;
	if (s1 == NULL)
		return (NULL);
	if (!(copy = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (copy);
	ft_strlcpy(copy, s1, (ft_strlen(s1) + 1));
	return (copy);
}
