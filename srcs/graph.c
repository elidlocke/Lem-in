/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:20:10 by enennige          #+#    #+#             */
/*   Updated: 2018/06/04 17:14:16 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

// get the number of ants
// get the number of elements in the array

//functions to write:
// - get input and create a linked list filled with a 'graph vertex' for each room
char	*read_input(void)
{
	char	*line;
	char	*vertex_lines;
	char	*path_lines;

	while (ft_getnextline(0, &line) > 0)
	{
		//if line is the first line, expect the number of ants
		//if line has format name x y, add it to the list of lines
		//if line has the format name1-name2, add it to the list of instructions
		printf("line! %s\n", line);
		
		ft_strdel(&line);
	}
	return ("YO DAWG");
}

// - use the unique index as the way to look up the graph

// - save the start point for the graph


