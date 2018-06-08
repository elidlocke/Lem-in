/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:33:43 by enennige          #+#    #+#             */
/*   Updated: 2018/06/07 19:16:07 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft.h"

// FOR DEBUGGING
# include <stdio.h>
// END DEBUGGING

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
	t_room		**rooms;
	t_list		**adj_list;
	t_list		**ant_routes;
}				t_anthill;

t_list		*read_input(void);

int     is_roomline(char *line);
int     is_tunnelline(char *line);

void    build_anthill(t_list *input_lines, t_anthill *anthill);
void    build_roomlist(t_list *input_lines, t_anthill *anthill);
void	build_adjlist(t_list *input_lines, t_anthill *anthill);

void    delete_roomlist(t_anthill *anthill);
void    delete_adjlist(t_anthill *anthill);
void    delete_inputlines(t_list **input_lines);

int	bfs(t_anthill *ah, int *pred, int *dist);
#endif
