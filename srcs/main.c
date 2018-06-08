#include "lemin.h"

void	print_roomlist(t_anthill anthill)
{
	int i;
	i = 0;
	while (i < anthill.num_rooms)
	{
		printf("[%d] room: %s\n", i, anthill.rooms[i]->name);
		i++;
	}
}

void	print_nodelist(t_anthill anthill)
{
	int i;
	t_list *node;
	i = 0;
	while (i < anthill.num_rooms)
	{
		node = anthill.adj_list[i];
		printf("parent: [%d]\n", *(int *)(node->content));
		while (node->next)
		{
			node = node->next;
			printf("	child: [%d]\n", *(int *)(node->content));
		}
		i++;
	}
}

int main(void)
{
	t_list		*input_lines;
	t_anthill	anthill;
	int		*pred;
	int		*dist;
	int		i;

	(void)anthill;
	input_lines = read_input();
	ft_printlst(input_lines);
	//TODO: validate the input
	build_anthill(input_lines, &anthill);
	print_roomlist(anthill);
	print_nodelist(anthill);

	pred = (int *)ft_memalloc(sizeof(*pred) * anthill.num_rooms);
	dist = (int *)ft_memalloc(sizeof(*dist) * anthill.num_rooms);
	if (!(bfs(&anthill, pred, dist)))
		ft_putstr("No path found.\n");
	else
	{
		i = anthill.end_idx;
		while (i != -1)
		{
			ft_putstr(anthill.rooms[i]->name);
			ft_putchar('(');
			ft_putnbr(i);
			ft_putchar(')');
			ft_putstr(" <- ");
			i = pred[i];
		}
	}


	delete_inputlines(&input_lines);
	delete_roomlist(&anthill);
	delete_adjlist(&anthill);
}
