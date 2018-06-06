/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:44:23 by enennige          #+#    #+#             */
/*   Updated: 2018/06/06 12:32:36 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*new_room(char *line, int index)
{
    t_room *room;
	int word_len;

	room = (t_room *)malloc(sizeof(t_room));
	if (!room)
		return NULL;
    word_len = 0;
    while (line[word_len] != ' ' && line[word_len] != '\0')
        word_len++;
    room->name = ft_strndup(line, word_len);
    room->unique_idx = index;
    room->parent_idx = -1;
	return (room);
}

void	delete_room(t_room *room)
{
    if (room)
	{
		ft_strdel(&(room->name));
		free(room);
	}
	room = NULL;
}


/*
void	add_tunnels(t_list *input_lines, t_list **graph)
{
	//look up the index, using the room name
	// add an item to the back of the linked list
}
*/

void    build_graph(t_list *input_lines, t_anthill *anthill)
{
    (void)anthill;

    t_list  **graph;
	t_room	*room;
	char	*line;
    int i;

    graph = (t_list **)malloc(sizeof(*graph) * (anthill->num_rooms));
    i = 0;
    while (i < anthill->num_rooms)
    {
		line = (char *)input_lines->content;
		if (is_roomline(line))
		{
			room = new_room((char *)input_lines->content, i);
			//printf("room name: %s & index: %d\n", room->name, room->unique_idx);
			graph[i] = ft_lstnew(room, sizeof(room));
			delete_room(room);	
			i++;
		}
		input_lines = input_lines->next;
    }
    printf("arrray element: %d is %s", 6, ((t_room *)graph[6]->content)->name);
	// now add the tunnels ! :O.
}
