/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 15:27:08 by enennige          #+#    #+#             */
/*   Updated: 2018/06/06 09:39:26 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Get a linked list of the input, line for line from the input terminal
*/

t_list	*read_input(void)
{	
	char	*line;
	t_list *lst;
	t_list	*node;

	line = NULL;
	lst = NULL;
	while (ft_getnextline(0, &line) > 0)
	{
		node = ft_lstnew(line, ft_strlen(line) + 1);
		if (lst == NULL)
			lst = node;
		else
			ft_lstadd(&lst, node);
		ft_strdel(&line);
	}
	ft_lstrev(&lst);
	return (lst);
}
