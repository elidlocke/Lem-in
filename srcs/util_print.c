/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:12:35 by enennige          #+#    #+#             */
/*   Updated: 2018/06/16 14:17:50 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

void	print_roomlist(t_anthill anthill)
{
	int i;

	i = 0;
	while (i < anthill.num_rooms)
	{
		printf("[%d] room: %s\n", i, anthill.rooms[i]->name);
		i++;
	}
}

void	print_nodelist(t_anthill anthill)
{
	int		i;
	t_list	*node;

	i = 0;
	while (i < anthill.num_rooms)
	{
		node = anthill.adj_list[i];
		printf("parent: [%d]\n", *(int *)(node->content));
		while (node->next)
		{
			node = node->next;
			printf("	child: [%d]\n", *(int *)(node->content));
		}
		i++;
	}
}

void	print_route(t_anthill *anthill, t_route *route)
{
	int i;
	int	*path;

	i = 0;
	path = route->path;
	while (path[i] != anthill->end_idx)
	{
		ft_putstr(anthill->rooms[path[i]]->name);
		ft_putchar('(');
		ft_putnbr(path[i]);
		ft_putchar(')');
		ft_putstr(" -> ");
		i++;
	}
	ft_putstr(anthill->rooms[path[i]]->name);
	ft_putchar('(');
	ft_putnbr(path[i]);
	ft_putstr(") [");
	ft_putnbr(route->cost);
	ft_putstr("]\n");
}

void    print_path(t_anthill *anthill, int *path)
{
	int i;

	i = 0;
	while (path[i] != anthill->end_idx)
	{
		printf("%s (%d) -> ", anthill->rooms[path[i]]->name, path[i]);
		i++;
	}
	printf("%s (%d)\n", anthill->rooms[path[i]]->name, path[i]);
}
