/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 13:44:01 by syndraum          #+#    #+#             */
/*   Updated: 2019/10/14 12:57:47 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *cursor;
	t_list *next_cursor;

	cursor = *lst;
	while (cursor != NULL)
	{
		next_cursor = cursor->next;
		ft_lstdelone(cursor, del);
		cursor = next_cursor;
	}
	*lst = NULL;
}
