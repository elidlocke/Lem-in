/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 19:15:02 by enennige          #+#    #+#             */
/*   Updated: 2018/06/16 19:17:54 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Iterates through all of the rooms until it finds a room name that matches
** the input string, then returns the index of the matching room name. Returns
** -1 on error.
*/

int	lookup_room_index(char *name, t_anthill *anthill)
{
	int		i;
	char	*current_name;

	i = 0;
	while (i < anthill->num_rooms)
	{
		current_name = (anthill->rooms[i]->name);
		if (ft_strcmp(name, current_name) == 0)
			return (i);
		i++;
	}
	return (-1);
}
