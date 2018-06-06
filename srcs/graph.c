/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:20:10 by enennige          #+#    #+#             */
/*   Updated: 2018/06/05 17:29:52 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// create a room structure
void	populate_room(t_room *room, char *line, int index)
{
	int word_len;
	
	word_len = 0;
	while (line[word_len] != ' ' && line[word_len] != '\0')
		word_len++;
	room->name = ft_strndup(line, word_len);
	room->unique_idx = index;
	room->parent_idx = -1;
}

void	clear_room(t_room *room)
{
	ft_strdel(&(room->name));
	room->unique_idx = -1;
	room->parent_idx = -1;
}

t_list	**make_graph(t_list *lines, t_anthill *anthill)
{
	t_room	room;
	t_list	**graph;
	int		index;
		
	if (!(graph = (t_list **)malloc(anthill->num_rooms * sizeof(t_list))))
		return (NULL);
	index = 0;
	while (index < anthill->num_rooms)
	{
		populate_room(&room, lines->content, index);
		graph[index] = ft_lstnew(&room, sizeof(room));
		clear_room(&room);
		index++;
		lines = lines->next;
	}
	return (graph);
}

void    read_input(void)
{
    char        *line;
    t_anthill   anthill;


    line = NULL;
    set_num_ants(line, &anthill);
    printf("num ants: %d\n\n", anthill.num_ants);
    t_list *lines = get_ll_lines(line, &anthill);
    ft_printlst(lines);
    printf("start node index: %d\n\n", anthill.start_idx);
    printf("end node index: %d\n\n", anthill.end_idx);
    printf("num nodes: %d\n\n", anthill.num_rooms);
	t_list **graph = make_graph(lines, &anthill);
	printf("node 1 name: %s", (char *)graph[0]->content.name);
}
