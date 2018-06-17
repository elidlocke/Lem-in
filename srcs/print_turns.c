/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_turns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 20:34:48 by enennige          #+#    #+#             */
/*   Updated: 2018/06/16 21:22:36 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Init the current ants to their first turn
*/

static void		init_current_ant_turn(t_ant *ants, int num_ants)
{
	int		i;
	t_ant	*ant;

	i = 0;
	while (i < num_ants)
	{
		ant = &(ants[i]);
		ant->current_turn = 1;
		i++;
	}
}

/*
** Increment the ant's state for a given turn
*/

static void		increment_ant_turn(t_ant *ant)
{
	if (ant->wait > 0)
		ant->wait = ant->wait - 1;
	else
		ant->current_turn += 1;
}

/*
** Print a single turn taken by the ants
*/

static void		print_a_turn(t_anthill *anthill, t_ant *ants)
{
	int i;
	int room_index;

	i = 0;
	while (i < anthill->num_ants)
	{
		if (ants[i].current_turn <= ants[i].route->cost
			&& ants[i].wait == 0)
		{
			ft_putchar('L');
			ft_putnbr(i + 1);
			ft_putchar('-');
			room_index = ants[i].route->path[ants[i].current_turn];
			ft_putstr(anthill->rooms[room_index]->name);
			ft_putchar(' ');
		}
		increment_ant_turn(&(ants[i]));
		i++;
	}
	ft_putchar('\n');
}

/*
** Loops through the ants and print all of the turns that need to be taken
** to get the ants from start to finish
*/

void			print_turns(t_anthill *anthill, t_ant *ants)
{
	int	turn;
	int	max_turns;

	init_current_ant_turn(ants, anthill->num_ants);
	turn = 1;
	max_turns = ants[anthill->num_ants - 1].turns_taken;
	while (turn <= max_turns)
	{
		print_a_turn(anthill, ants);
		turn++;
	}
}
