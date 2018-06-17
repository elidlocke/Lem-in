/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_roomlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 16:58:31 by enennige          #+#    #+#             */
/*   Updated: 2018/06/16 20:58:36 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Create a new room structure filling in the name and the index values
** based on the data from the text line passed in
*/

static t_room	*new_room(char *line, int index)
{
	t_room	*room;
	int		word_len;

	room = (t_room *)malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	word_len = 0;
	while (line[word_len] != ' ' && line[word_len] != '\0')
		word_len++;
	room->name = ft_strndup(line, word_len);
	room->unique_idx = index;
	room->parent_idx = -1;
	return (room);
}

/*
** Frees & deletes all the rooms in a list of rooms
*/

void			delete_roomlist(t_anthill *anthill)
{
	int		i;
	t_room	*room;

	if (anthill->rooms)
	{
		i = 0;
		while (i < anthill->num_rooms)
		{
			room = anthill->rooms[i];
			if (room)
			{
				ft_strdel(&(room->name));
				free(room);
			}
			anthill->rooms[i] = NULL;
			i++;
		}
	}
}

/*
** Sorts a list of rooms and checks if there are any duplicate names
** in the list. Returns 1 if valid, 0 if duplicates are found.
*/

static int		is_valid_roomlist(char **room_names, int num_rooms)
{
	int	i;

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

/*
** Takes the result of building the rooms out, validates it and saves the
** right information back into the anthill struct
*/

static void		set_room_data(t_anthill *anthill, char **room_names,
							t_room **rooms)
{
	room_names[anthill->num_rooms] = NULL;
	if (!(is_valid_roomlist(room_names, anthill->num_rooms)))
		anthill->is_valid = 0;
	anthill->rooms = rooms;
	ft_strarrdel(room_names);
}

/*
** Builds out a list of rooms and saves them into the anthill
*/

void			build_roomlist(t_list *input_lines, t_anthill *anthill)
{
	t_room	**rooms;
	char	**room_names;
	char	*line;
	int		i;

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
	set_room_data(anthill, room_names, rooms);
}
