/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_linetype.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:59:44 by enennige          #+#    #+#             */
/*   Updated: 2018/06/09 11:38:35 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Check if a line contains the number of ants and nothing else
*/
int		is_antcount(char *line)
{
	while (*line)
	{
		if (ft_isdigit(*line))
			line++;
		else
			return (0);
	}
	return (1);
}


/*
** Check if an input line is a valid room
*/

int     is_roomline(char *line)
{
    int space_count;
	int	word_flag;

    space_count = 0;
	word_flag = 0;
    while (*line)
    {
        if (*line == ' ')
		{
            word_flag = 1;
			space_count++;
		}
		else if (word_flag && !(ft_isdigit(*line)))
			return (0);
		line++;
    }
    if (space_count == 2)
        return (1);
    return (0);
}

/*
** Check if an input line is a tunnel line
*/

int     is_tunnelline(char *line)
{
    int dash_count;

    dash_count = 0;
    while (*line)
    {
        if (*line == '-')
            dash_count++;
        line++;
    }
    if (dash_count == 1)
        return (1);
    return (0);
}
