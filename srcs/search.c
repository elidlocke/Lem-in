#include "lemin.h"
#include <limits.h>

/* int	bfs(int *adj, int src, int dest, int num_vertices, int *pred, int *dist) */
int	bfs(t_anthill *ah, int *pred, int *dist)
{
	t_queue	*frontier_h;
	t_queue	*frontier_t;
	t_vertex *vertex;
	int	*explored;
	int	i;
	int	vertice_idx;

	if (!(explored = (int *)ft_memalloc(sizeof(*explored) * ah->num_vertices)))
		return (0);
	i = 0;
	while (i < ah->num_vertices)
	{
		explored[i] = 0;
		dist[i] = INT_MAX;
		pred[i] = -1;
	}
	explored[ah->start_idx] = 1;
	dist[ah->start_idx] = 0;
	enqueue(&frontier_h, &frontier_t, &ah->vertex_arr[ah->start_idx]);
	while (!queue_isempty(&frontier_h))
	{
		vertice_idx = *((int *)dequeue(&frontier_h, &frontier_t));
		vertex = &ah->vertex_arr[vertice_idx];
		while (vertex)
		{
			if (explored[vertex->unique_idx] == 0)
			{
				explored[vertex->unique_idx] = 1;
				dist[vertex->unique_idx] = dist[vertex->parent_idx] + 1;
				pred[vertex->unique_idx] = dist[vertex->parent_idx];

				if (vertex->unique_idx == ah->end_idx)
					return (1);
			}
		}
	}
	return (0);
}
