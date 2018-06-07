/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 09:40:52 by enennige          #+#    #+#             */
/*   Updated: 2018/06/06 17:01:41 by enennige         ###   ########.fr       */
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

	line = (char *)input_lines->content;
	anthill->num_ants = ft_atoi(line);
	//input_lines = input_lines->next;
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

void	build_anthill(t_list *input_lines, t_anthill *anthill)
{
	//TODO: rewrite to take **t_list and set the indexes
	set_num_ants(input_lines, anthill);
	set_indices(input_lines, anthill);
	build_roomlist(input_lines, anthill);
	build_adjlist(input_lines, anthill);
}
