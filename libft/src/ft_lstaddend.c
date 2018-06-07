/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:19:50 by enennige          #+#    #+#             */
/*   Updated: 2018/06/06 16:35:13 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
** The ft_lstaddend() function adds the element new at the end of the
** list alst.
*/

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list *node;

	node = *alst;
	while (node->next)
	{
		node = node->next;
	}
	node->next = new;
}
