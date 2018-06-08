/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 09:40:52 by enennige          #+#    #+#             */
/*   Updated: 2018/06/08 15:38:17 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Get the number of ants and save it in the anthill struct. Forwards the list
** pointer to the next line.
*/

void	set_num_ants(t_list *input_lines, t_anthill *anthill)
{
    char	*line;
	int		num_ants;

	line = (char *)input_lines->content;
	num_ants = ft_atoi(line);
	if (num_ants > 0)
		anthill->num_ants = num_ants;
}

/*
** Set the index values for the start and end rooms, and count the total
** number of rooms. Forwards the linked list to the first line after the
** room input lines
*/

void	set_indices(t_list *input_lines, t_anthill *anthill)
{
	char	*line;
	t_list	*current_node;
	int		index;

	current_node = input_lines;
	index = 0;
	while (current_node)
	{
		line = (char *)current_node->content;
		if (is_roomline(line))
			index++;
		else if (ft_strcmp(line, "##start") == 0)
			anthill->start_idx = index;
		else if (ft_strcmp(line, "##end") == 0)
			anthill->end_idx = index;
		else if (is_tunnelline(line))
		{
			anthill->num_rooms = index;
			return ;
		}
		current_node = current_node->next;
	}
}

/*
** Set the default values for the anthill struct
*/

void	init_anthill_defaults(t_anthill *anthill)
{
	anthill->num_ants = 0;
	anthill->start_idx = -1;
	anthill->end_idx = -1;
	anthill->num_rooms = 0;
	anthill->rooms = NULL;
	anthill->adj_list = NULL;
	anthill->ant_routes = NULL;
	anthill->is_valid = 1;
}

/*
** Check if the int values have been set for the anthill
*/

void    validate_anthill(t_anthill *anthill)
{
    if (anthill->num_ants < 1)
        anthill->is_valid = 0;
    else if (anthill->start_idx == -1 ||
			anthill->start_idx >= anthill->num_rooms)
        anthill->is_valid = 0;
    else if (anthill->end_idx == -1 ||
			anthill->end_idx >= anthill->num_rooms)
        anthill->is_valid = 0;
    else if (anthill->num_rooms < 2)
        anthill->is_valid = 0;
}

/*
** Build the anthill struct. Returns -1 if an error has occured
*/

int	build_anthill(t_list *input_lines, t_anthill *anthill)
{
	init_anthill_defaults(anthill);
	set_num_ants(input_lines, anthill);
	set_indices(input_lines, anthill);
	validate_anthill(anthill);
	if (anthill->is_valid)
	{
		build_roomlist(input_lines, anthill);
		if (anthill->is_valid == 0)
			return (-1);
		build_adjlist(input_lines, anthill);
		return (0);
	}
	return (-1);
}
