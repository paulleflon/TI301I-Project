#include <stdio.h>
#include <stdlib.h>
#include "../headers/cell.h"

// Create a cell: enter its value and the number of levels in the cell to obtain a pointer to the cell

t_cell* create_cell(int val, int nb_level){
	t_cell* new;
	new->value = val;
	new->nb_levels = nb_level;
	new->levels = (t_cell**)malloc(sizeof(t_cell*) * nb_level);
	return new;
}
