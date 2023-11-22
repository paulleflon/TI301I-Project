#include <stdlib.h>
#include "../headers/cell.h"

/**
 * Creates a level cell
 * @param val The value of the cell
 * @param nb_level The number of levels in the cell
 * @return A pointer to the created cell
 */
t_cell* create_cell(int val, int nb_level) {
	t_cell* new = (t_cell*)malloc(sizeof(t_cell));
	new->value = val;
	new->nb_levels = nb_level;
	new->levels = (t_cell**)malloc(sizeof(t_cell*) * nb_level);
	return new;
}
