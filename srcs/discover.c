/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpollore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 20:50:45 by jpollore          #+#    #+#             */
/*   Updated: 2018/06/16 20:55:22 by jpollore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		search_iter(t_anthill *anthill, t_route **route,
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

static void		reverse_adj_paths(t_anthill *ah, t_route *route)
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

static t_route	**search(t_anthill *anthill, int *iter)
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

static	void	reverse_routes(t_anthill *anthill, t_route **routes, int iter)
{
	int i;

	i = 0;
	while (i < iter)
		reverse_adj_paths(anthill, routes[i++]);
}

int				discover_routes(t_anthill *anthill)
{
	t_route	**routes;
	t_set	*head;
	t_set	*set;
	int		iter;
	int		num_routes;

	iter = 0;
	num_routes = 0;
	head = NULL;
	routes = NULL;
	while ((routes = search(anthill, &iter)) && iter)
	{
		if (!num_routes && (head = create_route_set(routes, iter)))
			set = head;
		else if ((set->next = create_route_set(routes, iter)))
			set = set->next;
		reverse_routes(anthill, routes, iter);
		num_routes++;
		iter = 0;
	}
	if (num_routes)
		choose_best_route_combo(anthill, head);
	free_set(head);
	return (!num_routes ? 0 : 1);
}
