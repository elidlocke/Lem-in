/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 15:27:08 by enennige          #+#    #+#             */
/*   Updated: 2018/06/05 17:29:56 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Get the number of ants and save it in the anthill struct. If the first line
*/

void	set_num_ants(char *line, t_anthill *anthill)
{
	ft_getnextline(0, &line);
	anthill->num_ants = ft_atoi(line);
}

/*
** Get the number of ants and save it in the anthill struct. If the first line
** is not a number, the function returns -1 for error
*/

void	set_start_end_indices(char **line, t_anthill *anthill, int index)
{
	if (ft_strcmp(*line, "##start") == 0)
	{
		ft_strdel(line);
		ft_getnextline(0, line);
		anthill->start_idx = index;
	}
	else if (ft_strcmp(*line, "##end") == 0)
	{
		ft_strdel(line);
		ft_getnextline(0, line);
		anthill->end_idx = index;
	}
}

/*
** Check if an input line is a valid room
*/
int		is_roomline(char *line)
{
	int space_count;
	
	space_count = 0;
	while (*line)
	{
		if (*line == ' ')
			space_count++;
		line++;
	}
	if (space_count == 2)
		return (1);
	return (0);
}

/*
** Get a linked list with all of the relevant input lines for the anthill,
** setting the index of the start vertex, end vertex and total number of
** vertices in the anthill in the process of creating the list.
*/

t_list	*get_ll_lines(char *line, t_anthill *anthill)
{	
	t_list *lst;
	t_list	*node;
	int		index;

	lst = NULL;
	index  = 0;
	while (ft_getnextline(0, &line) > 0)
	{
		set_start_end_indices(&line, anthill, index);
		if (line[0] != '#' && line[0] != 'L')
		{
			node = ft_lstnew(line, ft_strlen(line) + 1);
			if (lst == NULL)
				lst = node;
			else
				ft_lstadd(&lst, node);
			if (is_roomline(line)) 
				index++;
		}
		ft_strdel(&line);
	}
	anthill->num_rooms = index - 1;
	ft_lstrev(&lst);
	return (lst);
}
