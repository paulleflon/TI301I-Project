#include <stdio.h>
#include "headers/cell.h"
#include "headers/list.h"

int main() {
	int nb_levels[13] = {2, 1, 5, 1, 2, 1, 3, 1, 1, 2 , 1,4 ,1 };
	t_list *lst = create_list(5);
	printf("\n== Empty list ==\n\n");
	display_list(lst);
	for (int i = 0; i < 13; i++)
		insert_cell(lst, create_cell((13 - i)*2, nb_levels[i]));
	printf("\n== After inserting cells, level 1 display ==\n\n");
	display_level(lst, 1);
	printf("\n== After inserting cells, level 0 display ==\n\n");
	display_level(lst, 0);
	printf("\n== After inserting cells, basic display ==\n\n");
	display_list(lst);
	printf("\n== After inserting cells, aligned display ==\n\n");
	display_list_aligned(lst);
	printf("\n== After inserting a cell (value 17, 3 levels), aligned display ==\n\n");
	insert_cell_sorted(lst, create_cell(17, 3));
	display_list_aligned(lst);
	return 0;
}