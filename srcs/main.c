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

	(void)anthill;
	input_lines = read_input();
	ft_printlst(input_lines);
	//TODO: validate the input
	build_anthill(input_lines, &anthill);
	delete_inputlines(&input_lines);
	delete_roomlist(&anthill);
	delete_adjlist(&anthill);
	//sleep(30);
}
