/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:32:53 by enennige          #+#    #+#             */
/*   Updated: 2018/06/08 20:08:34 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_strarrdel() function takes as a parameter an array of strings that
** need to be freed with free(3), and sets each string to null.
*/

void	ft_strarrdel(char **str_arr)
{
	int		i;

	if (str_arr)
	{
		i = 0;
		while (str_arr[i] != NULL)
		{
			ft_strdel(&(str_arr[i]));
			i++;
		}
		free(str_arr);
		str_arr = NULL;
	}
}
