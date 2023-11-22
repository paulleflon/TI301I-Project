#include <stdio.h>
#include "headers/cell.h"
#include "headers/list.h"

int main() {
	int nb_levels[13] = {2, 1, 5, 1, 2, 1, 3, 1, 1, 2 , 1,4 ,1 };
	t_list *lst = create_list(5);
	for (int i = 0; i < 13; i++)
		insert_cell(lst, create_cell((13 - i)*2, nb_levels[i]));
	display_list(lst);
	insert_cell_sorted(lst, create_cell(45, 5));
	display_list(lst);
	return 0;
}