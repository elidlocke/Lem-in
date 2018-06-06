/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_linetype.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:59:44 by enennige          #+#    #+#             */
/*   Updated: 2018/06/06 12:11:24 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Check if an input line is a valid room
*/

int     is_roomline(char *line)
{
    int space_count;

    space_count = 0;
    while (*line)
    {
        if (*line == ' ')
            space_count++;
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
