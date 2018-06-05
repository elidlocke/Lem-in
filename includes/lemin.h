/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:33:43 by enennige          #+#    #+#             */
/*   Updated: 2018/06/04 17:15:14 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct	s_vertex
{
	char		*node_name;
	int			unique_index;
	int			parent_index;
	struct		s_vertex *next_vertex;
}				t_vertex;

typedef	struct	s_anthill
{
	int			num_ants;
	int			start_index;
	int			end_index;
	int			num_vertices;
	t_vertex	*vertex_arr;
}				t_anthill;

char	*read_input(void);
