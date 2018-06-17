/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 19:42:46 by enennige          #+#    #+#             */
/*   Updated: 2018/06/16 22:50:17 by enennige         ###   ########.fr       */
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
			if (!(discover_routes(&anthill, input_lines)))
				anthill.is_valid = 0;
			delete_inputlines(&input_lines);
			delete_roomlist(&anthill);
			delete_adjlist(&anthill);
		}
	}
	if (!anthill.is_valid)
		ft_putstr("ERROR\n");
	return (0);
}
