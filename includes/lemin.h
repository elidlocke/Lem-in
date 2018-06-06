/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:33:43 by enennige          #+#    #+#             */
/*   Updated: 2018/06/05 17:29:54 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft.h"
# include <stdio.h>

typedef struct	s_room
{
	char		*name;
	int			unique_idx;
	int			parent_idx;
}				t_room;

typedef	struct	s_anthill
{
	int			num_ants;
	int			start_idx;
	int			end_idx;
	int			num_rooms;
	t_list		*room_arr;
}				t_anthill;

void		read_input(void);
void		set_num_ants(char *line, t_anthill *anthill);
//void		set_start_end_indices(char **line, t_anthill *anthill, int index);
//int		is_roomline(char *line);
t_list		*get_ll_lines(char *line, t_anthill *anthill);

/* need to groom this */


#endif
