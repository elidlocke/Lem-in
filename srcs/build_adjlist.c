/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_adjlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:01:05 by enennige          #+#    #+#             */
/*   Updated: 2018/06/16 21:32:20 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Creates an array of linked list nodes, representing the indices of the
** rooms
*/

static void		create_adjlist(t_anthill *anthill)
{
	int		i;
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

/*
** Adds a linked list node to each linked list, drawing adjancies between the
** individual rooms in the array of linked lists. Finishes the adjacency list
** representation.
*/

static void		add_tunnels(t_list *input_lines, t_anthill *anthill)
{
	char	**room_names;
	int		room_from;
	int		room_to;
	t_list	*node;
	char	*line;

	line = (char *)input_lines->content;
	room_names = ft_strsplit(line, '-');
	room_from = lookup_room_index(room_names[0], anthill);
	room_to = lookup_room_index(room_names[1], anthill);
	ft_strarrdel(room_names);
	if (room_from == -1 || room_to == -1)
	{
		anthill->is_valid = 0;
		return ;
	}
	node = ft_lstnew(&room_from, sizeof(room_from));
	ft_lstaddend(&(anthill->adj_list)[room_to], node);
	node = ft_lstnew(&room_to, sizeof(room_to));
	ft_lstaddend(&(anthill->adj_list)[room_from], node);
}

/*
** Deletes a single child from the adjancency list
*/

void			delete_key_from_adjlist(t_anthill *anthill,
										int key_from, int key_to)
{
	t_list	*prev;
	t_list	*node;
	t_list	*next;

	node = anthill->adj_list[key_from];
	prev = NULL;
	next = NULL;
	while (node)
	{
		next = node->next;
		if (*(int *)(node->content) == key_to)
		{
			free(node->content);
			free(node);
			if (prev)
				prev->next = next;
			return ;
		}
		prev = node;
		node = next;
	}
}

/*
** Deletes the array of linked lists representing the rooms and tunnels in
** the anthill
*/

void			delete_adjlist(t_anthill *anthill)
{
	int		i;
	t_list	*node;
	t_list	*next;

	i = 0;
	while (i < anthill->num_rooms)
	{
		node = anthill->adj_list[i];
		while (node)
		{
			next = node->next;
			free(node->content);
			free(node);
			node = next;
		}
		i++;
	}
}

/*
** Builds and populates adjacency list representing the graph structure of
** the anthill
*/

void			build_adjlist(t_list *input_lines, t_anthill *anthill)
{
	char	*line;

	create_adjlist(anthill);
	while (input_lines)
	{
		line = (char *)input_lines->content;
		if (is_tunnelline(line))
			add_tunnels(input_lines, anthill);
		input_lines = input_lines->next;
	}
}
