/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpollore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 14:10:45 by jpollore          #+#    #+#             */
/*   Updated: 2018/06/09 17:32:47 by jpollore         ###   ########.fr       */
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

static int		explr(int *explored, t_search *info, t_list *vx, int *idx)
{
	explored[*(int *)vx->content] = 1;
	info->dist[*(int *)vx->content] = info->dist[idx[1]] + 1;
	info->pred[*(int *)vx->content] = idx[0];
	return (1);
}

static	void	free_ex_queue(int **ex, t_queue **head, t_queue **tail)
{
	free(*ex);
	while (!queue_isempty(head))
		dequeue(head, tail);
}

int				bfs(t_anthill *ah, t_search *info, t_route *ignore)
{
	t_queue	*head;
	t_queue	*tail;
	t_list	*vx;
	int		idx[2];
	int		*ex;

	if (!(ex = bfs_init(ah, info, ignore)))
		return (0);
	head = NULL;
	tail = NULL;
	enqueue(&head, &tail, &ah->start_idx);
	while (!queue_isempty(&head) && (vx = get_vrtx(ah, &head, &tail, idx)))
		while ((vx = vx->next))
		{
			if (ex[*(int *)vx->content])
				continue;
			if (explr(ex, info, vx, idx) && *(int *)vx->content == ah->end_idx)
			{
				free_ex_queue(&ex, &head, &tail);
				return (1);
			}
			enqueue(&head, &tail, (int *)vx->content);
		}
	free_ex_queue(&ex, &head, &tail);
	return (0);
}
