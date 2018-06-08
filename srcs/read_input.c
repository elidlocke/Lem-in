/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 15:27:08 by enennige          #+#    #+#             */
/*   Updated: 2018/06/08 15:10:03 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	delete_inputlines(t_list **input_lines)
{
	t_list	*next;
	t_list	*node;
	char	*line;

	if (input_lines)
	{
		node = *input_lines;
		while (node)
		{
			next = node->next;
			line = (char *)node->content;	
			ft_strdel(&line);
			free(node);
			node = next;
		}
		*input_lines = NULL;
	}
}

/*
** Check that the format of all of the input lines is correct
*/
int		validate_input_lines(t_list *input_lines)
{
	char	*line;
	int		i;
	int		started_tunnels;

	if (!input_lines)
		return (-1);
	i = 0;
	started_tunnels = 0;
	while (input_lines)
	{
		line = (char *)input_lines->content;
		if (i == 0 && !(is_antcount(line)))
			return (-1);
		if (i > 0 && is_tunnelline(line))
			started_tunnels = 1;
		if (i > 0 && started_tunnels == 0 &&
			!(is_roomline(line)) && line[0] != '#')
			return (-1);
		if (i > 0 && started_tunnels == 1 &&
			!(is_tunnelline(line)) && line[0] != '#')
			return (-1);
		input_lines = input_lines->next;
		i++;
	}
	return (0);
}

/*
** Get a linked list of the input, line for line from the input terminal
*/

t_list	*read_input(void)
{	
	char	*line;
	t_list *lst;
	t_list	*node;

	(void)node;
	line = NULL;
	lst = NULL;
	while (ft_getnextline(0, &line) > 0)
	{
		node = ft_lstnew(line, ft_strlen(line) + 1);
		if (lst == NULL)
			lst = node;
		else
			ft_lstadd(&lst, node);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	ft_lstrev(&lst);
	return (lst);
}
