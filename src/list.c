#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/list.h"

 /**
  * Creates an empty multi-level list
  * @param max_levels The maximum number of levels the list can support
  * @return A pointer to the created list
  */
t_list* create_list(int max_levels) {
	t_list *list = (t_list*)malloc(sizeof(t_list));
	list->heads = (t_cell**)malloc(sizeof(t_cell*) * max_levels);
	list->max_levels = max_levels;
	return list;
}


/**
 * Inserts a cell from the head of a multi-level list
 * @param list The list to insert the cell into
 * @param cell The cell to insert in the list
 */
void insert_cell(t_list* list, t_cell* cell) {
	// We have two conditions in case the cell has more levels than the list allows.
	for (int i = 0; i < cell->nb_levels && i < list->max_levels; i++) {
		cell->levels[i] = list->heads[i];
		list->heads[i] = cell;
	}
}

/**
 * Displays all the nodes of a list in a given level
 * @param list The list to display
 * @param level The level to display
 */
void display_level(t_list* list, int level) {
	t_cell *temp = list->heads[level];
	if (temp == NULL)
		printf("[list head_%d @-]-->NULL\n", level);
	else {
		printf("[list head_%d @-]-->",level);
		while(temp != NULL) {
			printf("[ %d|@-]-->", temp->value);
			temp = temp ->levels[level];
		}
		printf(" NULL\n");
    }
}

/**
 * Displays an hyphen line of a given length
 * @param length The length of the line to display
 */
void display_line(int length) {
	for (int i = 0; i < length; i++)
		printf("-");
}

/**
 * Displays all levels of a list, aligning the cells at each level
 * @param list The list to display
 */
void display_list_aligned(t_list* list){
	// The alignment reference will always be the first level,
	// As it includes all the cells
	t_cell *temp, *temp_level1;
	display_level(list, 0); // The first level can be displayed as usual
	for (int i = 1; i < list->max_levels; i++) { // Logic for each level
		temp = list->heads[i];
		temp_level1 = list->heads[0];
		printf("[list head_%d @-]--", i);
		// If this level points to nothing, we just have to
		// Display a line until level 1 reaches null.
		if (temp == NULL) {
			while (temp_level1 != temp) {
				// To set a blank line instead of a level,
				// The line must be 10 characters long for 1 digit.
				// Then we add to its length if the reference cell has more digits
				// The number of additional digits is given by log10, converted to an integer.
				display_line(10 + (int)log10(temp_level1->value));
				temp_level1 = temp_level1->levels[0];
			}
			printf("> NULL\n");
		}
		else {
			while (temp != NULL) {
				// If the current level cell doesn't match level 1,
				// We display blank line until they match again.
				while (temp_level1 != temp && temp_level1->levels[0]) {
					display_line(10 + (int)log10(temp_level1->value));
					temp_level1 = temp_level1->levels[0];
				}
				// When it finally matches, we display the cell as usual
				if (temp == temp_level1) {
					printf(">[ %d|@-]--", temp->value);
					temp_level1 = temp_level1->levels[0];
				}
				temp = temp->levels[i];
			}
			// Then, if this level stops before level 1,
			// We keep printing a blank line to align the end of each level
			while (temp_level1) {
				display_line(10 + (int)log10(temp_level1->value));
				temp_level1 = temp_level1->levels[0];
			}
			printf("> NULL\n");
		}
	}
}

/**
 * Displays all levels of a list
 * @param list The list to display
 */
void display_list(t_list* list){
	for (int i=0; i<list->max_levels; i++)
		display_level(list, i);
}


/**
 * Inserts a level cell while keeping the list sorted (simple implementation, no optimization)
 * @param list The list to insert into
 * @param cell The cell to insert
 */
void insert_cell_sorted(t_list* list, t_cell* cell) {
	int i;
	t_cell *current;
	// We perform the insertion at each level.
	for (i = 0; i < cell->nb_levels; i++) {
		current = list->heads[i];
		// If the first cell of the level is greater than the cell we want to insert,
		// It means that we have to bind this cell directly to the list's head at this level,
		// And all the ones below since a lower level can't have a smaller entry point.
		// So we get out of this loop and go to the following one.
		if (!current || current->value > cell->value)
			// break is not always considered a good practice,
			// but with good commenting, it **is** okay.
			break;
		// Now, we search for the cell we will insert our new cell from.
		// If our new cell is greater than every cell in the level,
		// The second part of the condition will try to access a null pointer
		// So the first part prevents it and stops the loop if we reached the last cell of the level.
		while (current->levels[i] && current->levels[i]->value < cell->value)
			current = current->levels[i];
		// Then, we perform a usual insert.
		cell->levels[i] = current->levels[i];
		current->levels[i] = cell;
	}
	// Then, for all the levels where the cell we want to insert is the smallest,
	// We bind this cell to the list head.
	// The syntax here can be confusing:
	// Since we may have stopped the previous loop before the end,
	// We already handled the i first levels, now we must make sure the remaining levels
	// Are also handled (that is binding the cell to the list heads)
	// So we don't reassign i, and just start with value i had when we exited the previous loop.
	for (;i < cell->nb_levels; i++) {
		cell->levels[i] = list->heads[i];
		list->heads[i] = cell;
	}
}