/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_adjlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:01:05 by enennige          #+#    #+#             */
/*   Updated: 2018/06/06 17:33:21 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int     lookup_room_index(char *name, t_anthill *anthill)
{
    int i;
    char *current_name;

    i = 0;
    while (i < anthill->num_rooms)
    {
        current_name = (anthill->rooms[i]->name;
        if (ft_strcmp(name, current_name) == 0)
            return (i);
        i++;
    }
    return (-1);
}

/*
void    add_tunnels(t_list *input_lines, t_anthill *anthill)
{
    char    **room_names;
    int     room_from;
    int     room_to;

    // TODO: need to free this later !!
    room_names = ft_strsplit((char *)input_lines->content, '-');
    room_from = lookup_room_index(room_names[0], anthill);
    room_to = lookup_room_index(room_names[1], anthill);
    // add a free string array function to library & insert here
    //printf("tunnel from: %d to %d\n", room_from, room_to);
    ft_lstadd(&(anthill->graph[room_from]), anthill->graph[room_to]);
    ft_lstrev(&(anthill->graph[room_from]));

    ft_lstadd(&(anthill->graph[room_to]), anthill->graph[room_from]);
    ft_lstrev(&(anthill->graph[room_to]));
}
*/

void	build_adjlist(t_list *input_lines, t_anthill *anthill)
{
	(void)input_lines;
	(void)anthill;	
}
