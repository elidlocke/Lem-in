/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:33:43 by enennige          #+#    #+#             */
/*   Updated: 2018/06/16 14:42:58 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft.h"
# include <limits.h>

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
	int			is_valid;
}				t_anthill;

typedef struct	s_route
{
	int			*path;
	int			cost;
	int			num_ants;
}				t_route;

typedef struct	s_search
{
	int			*pred;
	int			*dist;
}				t_search;

typedef struct	s_ant
{
	t_route		*route;
	int			wait;
	int			turns_taken;
	int			current_turn;
}				t_ant;

t_list			*read_input(void);

int				is_antcount(char *line);
int				is_roomline(char *line);
int				is_tunnelline(char *line);

int				validate_input_lines(t_list *input_lines);

int				build_anthill(t_list *input_lines, t_anthill *anthill);
void			build_roomlist(t_list *input_lines, t_anthill *anthill);
void			build_adjlist(t_list *input_lines, t_anthill *anthill);

void			delete_roomlist(t_anthill *anthill);
void			delete_adjlist(t_anthill *anthill);
void			delete_inputlines(t_list **input_lines);

int				bfs(t_anthill *ah, t_search *info, t_route *ignore);
int				solve(t_anthill *anthill);
void			delete_key_from_adjlist(t_anthill *anthill, int key_from, int key_to);
void			choose_routes(t_anthill *anthill, t_route **routes,
					int num_routes);
void			print_turns(t_anthill *anthill, t_ant *ants);

// DEBUGGING PRINT FUNCTIONS //
void    print_roomlist(t_anthill anthill);
void    print_nodelist(t_anthill anthill);
void    print_route(t_anthill *anthill, t_route *route);
void    print_path(t_anthill *anthill, int *path);
// END DEBUGGING PRINT FUNCTIONS //

#endif
