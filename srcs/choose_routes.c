/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_routes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 13:41:36 by enennige          #+#    #+#             */
/*   Updated: 2018/06/16 10:03:22 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Init all the routes to have zero ants on them
*/

void	init_ants_on_route(t_route **routes, int num_routes)
{
	int i;

	i = 0;
	while (i < num_routes)
	{
		routes[i]->num_ants = 0;
		i++;
	}
}

/*
** Given a list of routes, get the shortest route that an ant can take,
** using the 'real' path cost of each route, which is the cost of the
** route, plus the number of ants already on that route.
*/

int		get_shortest_route_index(t_route **routes, int num_routes)
{
	int	i;
	int	real_path_cost;
	int	min_path_cost;
	int	min_path_idx;

	min_path_cost = routes[0]->cost + routes[0]->num_ants;
	min_path_idx = 0;
	i = 1;
	while (i < num_routes)
	{
		real_path_cost = routes[i]->cost + routes[i]->num_ants;
		if (real_path_cost < min_path_cost)
			min_path_idx = i;
		i++;
	}
	return (min_path_idx);
}

/*
** Loop through all the ants and find the optimal route for each ant
*/

void	choose_routes(t_anthill *anthill, t_route **routes, int num_routes)
{
	int		i;
	int		route_idx;
	t_ant	ants[anthill->num_ants];

	i = 0;
	init_ants_on_route(routes, num_routes);
	while (i < anthill->num_ants)
	{
		route_idx = get_shortest_route_index(routes, num_routes);
		ants[i].wait = routes[route_idx]->num_ants;
		routes[route_idx]->num_ants = routes[route_idx]->num_ants + 1;
		ants[i].route = routes[route_idx];
		ants[i].turns_taken = routes[route_idx]->cost + ants[i].wait;
		i++;
	}
	print_turns(anthill, ants);
}
