/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort_merge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 13:59:25 by enennige          #+#    #+#             */
/*   Updated: 2018/06/12 21:28:52 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	merge(char **str, int start, int mid, int end)
{
	int		i_copy;
	int		i_side[2];
	char	**copy;

	if (!(copy = (char **)malloc(sizeof(char *) * (end - start + 1))))
		return ;
	i_copy = 0;
	i_side[0] = start;
	i_side[1] = mid + 1;
	while (i_side[0] <= mid && i_side[1] <= end)
	{
		if (ft_strcmp(str[i_side[1]], str[i_side[0]]) > 0)
			copy[i_copy++] = str[i_side[0]++];
		else
			copy[i_copy++] = str[i_side[1]++];
	}
	while (i_side[0] <= mid)
		copy[i_copy++] = str[i_side[0]++];
	while (i_side[1] <= end)
		copy[i_copy++] = str[i_side[1]++];
	i_copy = -1;
	while (++i_copy < (end - start + 1))
		str[start + i_copy] = copy[i_copy];
	if (copy)
		free(copy);
}

static void	merge_sort_recursion(char **str, int start, int end)
{
	int mid;

	if (start == end)
		return ;
	mid = (start + end) / 2;
	merge_sort_recursion(str, start, mid);
	merge_sort_recursion(str, mid + 1, end);
	merge(str, start, mid, end);
}

/*
** ft_strsort_merge() takes a list of integers and the length of the
** array and then sorts the numbers recursively in nlog(n) time.
** NOTE: The length should not include the null terminator!
*/

void		ft_strsort_merge(char **str, int len)
{
	merge_sort_recursion(str, 0, len - 1);
}
