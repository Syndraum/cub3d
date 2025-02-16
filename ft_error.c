/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:56:26 by roalvare          #+#    #+#             */
/*   Updated: 2020/01/03 19:48:24 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(int error)
{
	if (error == -1)
		perror("");
	else if (error <= 102)
		ft_putendl_fd(strerror(error), 2);
	else if (error == 103)
		ft_putendl_fd("File .cub needed", 2);
	return (EXIT_FAILURE);
}

int	print_error(char *error, t_list *elmt)
{
	ft_lstdelone(elmt, free_maps);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error, 2);
	return (-1);
}
