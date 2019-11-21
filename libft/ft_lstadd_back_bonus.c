/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:56:55 by roalvare          #+#    #+#             */
/*   Updated: 2019/10/12 13:13:48 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *cursor;

	if (*alst != NULL)
	{
		cursor = *alst;
		while (cursor->next != NULL)
			cursor = cursor->next;
		cursor->next = new;
	}
	else
		*alst = new;
}
