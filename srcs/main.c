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


int main(void)
{
	t_list		*input_lines;
	t_anthill	anthill;

	input_lines = read_input();
	ft_printlst(input_lines);
	//TODO: validate the input
	build_anthill(input_lines, &anthill);
	// TODO: Free the linked list input_lines
	// TODO: Free each of the rooms
	//printf("num lines in anthill: %d\n", anthill.num_ants);	
	//printf("start index: %d\n", anthill.start_idx);	
	//printf("end index: %d\n", anthill.end_idx);	
	//printf("num rooms: %d\n", anthill.num_rooms);
	print_roomlist(anthill);
}
