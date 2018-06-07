/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_roomlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 16:58:31 by enennige          #+#    #+#             */
/*   Updated: 2018/06/07 09:54:16 by enennige         ###   ########.fr       */
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

void	delete_roomlist(t_anthill *anthill)
{
	int i;

	if (anthill->rooms)
	{
		i = 0;
		while (i < anthill->num_rooms)
		{
			delete_room(anthill->rooms[i]);
			i++;
		}
	}
}

void    build_roomlist(t_list *input_lines, t_anthill *anthill)
{
    (void)anthill;

    t_room	**rooms;
	t_room	*room;
	char	*line;
    int i;

    rooms = (t_room **)malloc(sizeof(*rooms) * (anthill->num_rooms));
    i = 0;
    while (i < anthill->num_rooms)
    {
		line = (char *)input_lines->content;
		if (is_roomline(line))
		{
			room = new_room((char *)input_lines->content, i);
			//printf("room name: %s & index: %d\n", room->name, room->unique_idx);
			rooms[i] = room;
			i++;
		}
		input_lines = input_lines->next;
    }
	anthill->rooms = rooms;
}
