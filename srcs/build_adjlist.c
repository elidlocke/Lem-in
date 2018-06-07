/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_adjlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:01:05 by enennige          #+#    #+#             */
/*   Updated: 2018/06/06 21:18:30 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int     lookup_room_index(char *name, t_anthill *anthill)
{
    int i;
    char *current_name;

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

void	create_adjlist(t_anthill *anthill)
{
	int i;
	t_list	*node;
	t_list	**node_arr;

	node_arr = (t_list **)malloc(sizeof(*node_arr) * (anthill->num_rooms));
	i = 0;
	while (i < anthill->num_rooms)
	{
		node = ft_lstnew(&i, sizeof(i));
		node_arr[i] = node;
		i++;
	}
	anthill->adj_list = node_arr;
}

void    add_tunnels(t_list *input_lines, t_anthill *anthill)
{
    char    **room_names;
    int     room_from;
    int     room_to;
	t_list	*node;

    room_names = ft_strsplit((char *)input_lines->content, '-');
    room_from = lookup_room_index(room_names[0], anthill);
    room_to = lookup_room_index(room_names[1], anthill);
    // TODO: need to free the strings from strsplit!!
    //printf("tunnel from: %d to %d\n", room_from, room_to);
	node = ft_lstnew(&room_from, sizeof(room_from));
    ft_lstaddend(&(anthill->adj_list)[room_to], node);
	node = ft_lstnew(&room_to, sizeof(room_to));
    ft_lstaddend(&(anthill->adj_list)[room_from], node);
}

void	build_adjlist(t_list *input_lines, t_anthill *anthill)
{
	char	*line;
	
	create_adjlist(anthill);
	while (input_lines)
	{
		line = (char *)input_lines->content;
		if (is_tunnelline(line))
		{
			add_tunnels(input_lines, anthill);
		}
		input_lines = input_lines->next;
	}
}
