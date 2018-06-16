/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 19:42:46 by enennige          #+#    #+#             */
/*   Updated: 2018/06/16 14:44:10 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(void)
{
	t_list		*input_lines;
	t_anthill	anthill;

	if ((input_lines = read_input()) &&
			validate_input_lines(input_lines) != -1)
	{
		if (build_anthill(input_lines, &anthill) != -1)
		{
			//TODO: REMOVE DEBUGGING PRINT STATEMENT
			//delete_key_from_adjlist(&anthill, 0, 1);
			print_nodelist(anthill);
			// END
			if (!(solve(&anthill)))
				ft_putstr("ERROR\n");
			delete_inputlines(&input_lines);
			delete_roomlist(&anthill);
			delete_adjlist(&anthill);
			return (0);
		}
	}
	ft_putstr("ERROR\n");
	return (-1);
}
