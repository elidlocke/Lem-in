/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort_merge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 13:59:25 by enennige          #+#    #+#             */
/*   Updated: 2018/06/08 20:29:38 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	merge(char **str, int start, int mid, int end)
{
	int		i_copy;
	int		i_left;
	int		i_right;
	char	**copy;
	
	if (!(copy = (char **)malloc(sizeof(char *) * (end - start + 1))))
		return ;
	i_copy = 0;
	i_left = start;
	i_right = mid + 1;
	while (i_left <= mid && i_right <= end)
	{
		if(ft_strcmp(str[i_right], str[i_left]) > 0)
			copy[i_copy++] = str[i_left++];
		else
			copy[i_copy++] = str[i_right++];
	}
	while (i_left <= mid)
		copy[i_copy++] = str[i_left++];
	while (i_right <= end)
		copy[i_copy++] = str[i_right++];
	i_copy = 0;
	while (i_copy < (end - start + 1))
	{
		str[start + i_copy] = copy[i_copy];
		i_copy++;
	}
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
