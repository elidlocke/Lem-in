/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 19:42:46 by enennige          #+#    #+#             */
/*   Updated: 2018/06/08 16:17:41 by jpollore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
	int i;
	t_list *node;
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

void	solve(t_anthill *anthill)
{
	int		*pred;
	int		*dist;
	int		*ignore;
	t_route		**routes;

	int		i;
	int		iter;
	int		path_cost;
	size_t		ignore_size;

	pred = (int *)ft_memalloc(sizeof(*pred) * anthill->num_rooms);
	dist = (int *)ft_memalloc(sizeof(*dist) * anthill->num_rooms);
	routes = (t_route **)ft_memalloc(sizeof(*routes) * anthill->num_ants);

	iter = 0;
	ignore_size = 0;
	ignore = NULL;
	while (iter < anthill->num_ants && bfs(anthill, pred, dist, ignore, ignore_size))
	{
		i = anthill->end_idx;
		path_cost = dist[i];
		routes[iter] = create_route(path_cost);
		while (i != -1)
		{
			routes[iter]->path[path_cost--] = i;
			if (i != anthill->end_idx && i != anthill->start_idx)
				ignore = ft_iarrappend(ignore, ignore_size++, i);
			i = pred[i];
		}
		iter++;
	}
	i = 0;
	while (i < iter)
		print_route(anthill, routes[i++]);
}

int main(void)
{
	t_list		*input_lines;
	t_anthill	anthill;

	input_lines = read_input();
	if (validate_input_lines(input_lines) != -1)
	{
		if (build_anthill(input_lines, &anthill) != -1)
		{
			//print_roomlist(anthill);
			//print_nodelist(anthill);
			ft_putstr("FINDING PATH\n");
			solve(&anthill);
			delete_inputlines(&input_lines);
			delete_roomlist(&anthill);
			delete_adjlist(&anthill);
			return (0);
		}
	}
	ft_putstr("ERROR\n");
	return (-1);
}
