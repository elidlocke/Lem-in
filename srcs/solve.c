/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpollore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 14:11:17 by jpollore          #+#    #+#             */
/*   Updated: 2018/06/09 20:16:18 by jpollore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		print_route(t_anthill *anthill, t_route *route)
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

static t_route	*create_route(int path_cost)
{
	t_route *route;

	if ((route = (t_route *)ft_memalloc(sizeof(*route))))
	{
		route->cost = path_cost;
		route->path = (int *)ft_memalloc(sizeof(int) * path_cost + 1);
	}
	return (route);
}

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
	return (routes);
}

void			free_routes(t_route **arr, int size)
{
	int i;

	if (!size)
		return ;
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

int				solve(t_anthill *anthill)
{
	int		i;
	int		iter;
	t_route **routes;

	iter = 0;
	routes = search(anthill, &iter);
	i = 0;
	while (i < iter)
		print_route(anthill, routes[i++]);
	if (iter > 0)
		find_routes(anthill, routes, iter);
	free_routes(routes, iter);
	return (!iter ? 0 : 1);
}
