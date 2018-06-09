/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_roomlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 16:58:31 by enennige          #+#    #+#             */
/*   Updated: 2018/06/09 11:39:00 by enennige         ###   ########.fr       */
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

int		is_valid_roomlist(char **room_names, int num_rooms)
{
    int i;

	ft_strsort_merge(room_names, num_rooms);
    i = 1;
    while (i < num_rooms)
    {
        if (ft_strcmp(room_names[i], room_names[i - 1]) == 0)
            return (0);
        i++;
    }
    return (1);
}

void    build_roomlist(t_list *input_lines, t_anthill *anthill)
{
    t_room	**rooms;
	char	**room_names;
	char	*line;
    int i;

    if (!(rooms = (t_room **)malloc(sizeof(*rooms) * (anthill->num_rooms))))
		return ;
    if (!(room_names = (char **)malloc(sizeof(char *) *
		(anthill->num_rooms) + 1)))
			return ;
    i = 0;
    while (i < anthill->num_rooms)
    {
		line = (char *)input_lines->content;
		if (is_roomline(line))
		{
			rooms[i] = new_room((char *)input_lines->content, i);
			room_names[i] = ft_strdup(rooms[i]->name);
			i++;
		}
		input_lines = input_lines->next;
    }
	room_names[i] = NULL;
	if (is_valid_roomlist(room_names, anthill->num_rooms))
		anthill->rooms = rooms;
	else
		anthill->is_valid = 0;
	ft_strarrdel(room_names);
}
