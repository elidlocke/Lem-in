/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpollore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 14:11:17 by jpollore          #+#    #+#             */
/*   Updated: 2018/06/16 20:11:19 by enennige         ###   ########.fr       */
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

int		search_iter(t_anthill *anthill, t_route **route,
							t_search *info, t_route *ignore)
{
	int	i;
	int	path_cost;
	int	*tmp_path;

	if (!(bfs(anthill, info, ignore)))
		return (0);
	i = anthill->end_idx;
	path_cost = info->dist[i];
	(*route) = create_route(path_cost);
	while (i != -1)
	{
		(*route)->path[path_cost--] = i;
		if (i != anthill->end_idx && i != anthill->start_idx)
		{
			tmp_path = ignore->path;
			ignore->path = ft_iarrappend(tmp_path, ignore->cost++, i);
			free(tmp_path);
			tmp_path = NULL;
		}
		i = info->pred[i];
	}
	return (1);
}

void		reverse_adj_paths(t_anthill *ah, t_route *route)
{
	int		i;
	t_list	*parent;

	i = route->cost;
	while (i >= 0)
	{
		if (route->path[i] != ah->end_idx)
		{
			parent = ah->adj_list[route->path[i]];
			delete_key_from_adjlist(ah, *(int *)parent->content,
									route->path[i + 1]);
		}
		i--;
	}
}

t_route	**search(t_anthill *anthill, int *iter)
{
	t_search	info;
	t_route		**routes;
	t_route		ignore;

	info.pred = (int *)ft_memalloc(sizeof(int) * anthill->num_rooms);
	info.dist = (int *)ft_memalloc(sizeof(int) * anthill->num_rooms);
	routes = (t_route **)ft_memalloc(sizeof(*routes) * anthill->num_ants);
	ignore.cost = 0;
	ignore.path = NULL;
	while (*iter < anthill->num_ants &&
			search_iter(anthill, &routes[*iter], &info, &ignore))
		(*iter)++;
	free(info.pred);
	free(info.dist);
	free(ignore.path);
	if (!(*iter))
	{
		free(routes);
		routes = NULL;
	}
	return (routes);
}

void			free_routes(t_route **arr, int size)
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

void			free_set(t_set *set)
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

t_set			*create_route_set(t_route **routes, int size)
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

int				solve(t_anthill *anthill)
{
	t_route	**routes;
	t_set	*head;
	t_set	*set;
	int		iter;
	int		num_routes;
	int		i;

	iter = 0;
	num_routes = 0;
	head = NULL;
	routes = NULL;
	while ((routes = search(anthill, &iter)) && iter)
	{
		if (!num_routes)
		{
			head = create_route_set(routes, iter);
			set = head;
		}
		else
		{
			set->next = create_route_set(routes, iter);
			set = set->next;
		}
		i = 0;
		while (i < iter)
			reverse_adj_paths(anthill, routes[i++]);
		num_routes++;
		iter = 0;
	}
	// resolve_conflicts(anthill, head, num_routes);
	if (num_routes)
		choose_best_route_combo(anthill, head);
	free_set(head);
	return (!num_routes ? 0 : 1);
}
