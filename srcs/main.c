#include "lemin.h"

int main(void)
{
	t_list		*input_lines;
	t_anthill	anthill;

	input_lines = read_input();
	ft_printlst(input_lines);
	//TODO: validate the input
	build_anthill(input_lines, &anthill);
	printf("num lines in anthill: %d\n", anthill.num_ants);	
	printf("start index: %d\n", anthill.start_idx);	
	printf("end index: %d\n", anthill.end_idx);	
	printf("num rooms: %d\n", anthill.num_rooms);
	// TODO: Free the linked list input_lines
}
