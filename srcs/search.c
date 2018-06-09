/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpollore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 14:10:45 by jpollore          #+#    #+#             */
/*   Updated: 2018/06/09 16:26:01 by jpollore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		*bfs_init(t_anthill *ah, t_search *info, t_route *ignore)
{
	int	i;
	int	*explored;

	if (!(explored = (int *)ft_memalloc(sizeof(*explored) * ah->num_rooms)))
		return (NULL);
	i = 0;
	while (i < ah->num_rooms)
	{
		if (ignore->cost && ft_iarrhas(ignore->path, ignore->cost, i))
			explored[i] = 1;
		else
			explored[i] = 0;
		info->dist[i] = INT_MAX;
		info->pred[i] = -1;
		i++;
	}
	explored[ah->start_idx] = 1;
	info->dist[ah->start_idx] = 0;
	return (explored);
}

static t_list	*get_vrtx(t_anthill *ah, t_queue **frontier_h,
			t_queue **frontier_t, int *idx)
{
	idx[0] = *((int *)dequeue(frontier_h, frontier_t));
	if (idx[0] != ah->start_idx)
		idx[1] = *(int *)ah->adj_list[idx[0]]->content;
	else
		idx[1] = ah->start_idx;
	return (ah->adj_list[idx[0]]);
}

int				bfs(t_anthill *ah, t_search *info, t_route *ignore)
{
	t_queue	*frntr_h;
	t_queue	*frntr_t;
	t_list	*vrtx;
	int		idx[2];
	int		*explored;

	if (!(explored = bfs_init(ah, info, ignore)))
		return (0);
	frntr_h = NULL;
	frntr_t = NULL;
	enqueue(&frntr_h, &frntr_t, &ah->start_idx);
	while (!queue_isempty(&frntr_h) &&
			(vrtx = get_vrtx(ah, &frntr_h, &frntr_t, idx)))
		while ((vrtx = vrtx->next))
		{
			if (explored[*(int *)vrtx->content])
				continue;
			explored[*(int *)vrtx->content] = 1;
			info->dist[*(int *)vrtx->content] = info->dist[idx[1]] + 1;
			info->pred[*(int *)vrtx->content] = idx[0];
			if (*(int *)vrtx->content == ah->end_idx)
				return (1);
			enqueue(&frntr_h, &frntr_t, (int *)vrtx->content);
		}
	return (0);
}
