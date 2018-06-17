/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpollore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 20:54:37 by jpollore          #+#    #+#             */
/*   Updated: 2018/06/16 20:55:03 by jpollore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_route	*create_route(int path_cost)
{
	t_route *route;

	if ((route = (t_route *)ft_memalloc(sizeof(*route))))
	{
		route->cost = path_cost;
		route->path = (int *)ft_memalloc(sizeof(int) * path_cost + 1);
	}
	return (route);
}

void	free_routes(t_route **arr, int size)
{
	int i;

	if (!size)
	{
		free(arr);
		arr = NULL;
		return ;
	}
	i = 0;
	while (i < size)
	{
		free(arr[i]->path);
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_set(t_set *set)
{
	t_set *tmp;

	while (set)
	{
		free_routes(set->routes, set->size);
		tmp = set;
		set = set->next;
		free(tmp);
	}
	free(set);
	set = NULL;
}

t_set	*create_route_set(t_route **routes, int size)
{
	t_set *set;

	if ((set = (t_set *)ft_memalloc(sizeof(*set))))
	{
		set->routes = routes;
		set->size = size;
		set->next = NULL;
	}
	return (set);
}
