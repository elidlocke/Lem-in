#include "lemin.h"
#include <limits.h>

int	bfs(t_anthill *ah, int *pred, int *dist)
{
	t_queue	*frontier_h;
	t_queue	*frontier_t;
	t_list	*vertex;
	int	*explored;
	int	i;
	int	parent_idx;
	int	vertice_idx;

	if (!(explored = (int *)ft_memalloc(sizeof(*explored) * ah->num_rooms)))
		return (0);
	i = 0;
	while (i < ah->num_rooms)
	{
		explored[i] = 0;
		dist[i] = INT_MAX;
		pred[i] = -1;
		i++;
	}
	explored[ah->start_idx] = 1;
	dist[ah->start_idx] = 0;
	frontier_h = NULL;
	frontier_t = NULL;
	enqueue(&frontier_h, &frontier_t, &ah->start_idx);
	while (!queue_isempty(&frontier_h))
	{
		vertice_idx = *((int *)dequeue(&frontier_h, &frontier_t));
		if (vertice_idx != ah->start_idx)
			parent_idx = *(int *)ah->adj_list[vertice_idx]->content;
		else
			parent_idx = ah->start_idx;
		vertex = ah->adj_list[vertice_idx]->next;
		while (vertex)
		{
			i = *((int *)vertex->content);
			if (explored[i] == 0)
			{
				explored[i] = 1;
				dist[i] = dist[parent_idx] + 1;
				pred[i] = parent_idx;

				if (i == ah->end_idx)
					return (1);
				enqueue(&frontier_h, &frontier_t, &i);
			}
			vertex = vertex->next;
		}
	}
	return (0);
}
