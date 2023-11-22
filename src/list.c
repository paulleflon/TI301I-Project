#include <stdio.h>
#include <stdlib.h>
#include "../headers/list.h"

// Create an empty level list: we'll give the maximum number of levels this list can have
 
t_list* create_list(int max_levels) {
	t_list *list = (t_list*)malloc(sizeof(t_list));
	list->heads = (t_cell**)malloc(sizeof(t_cell*) * max_levels);
	list->max_levels = max_levels;
	return list;
}

//Insert a cell with levels at the beginning (head) of the list (be careful to take into account the number of levels in the cell) 

void insert_cell(t_list* list, t_cell* cell) {
	// We have two conditions  in case the cell has more levels than the list allows.
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
	if (temp == NULL){
		printf("[list head_%d @-]-->NULL\n",level);
	}
	else{
		printf("[list head_%d @-]--> ",level);
		while(temp != NULL){
			printf("[ %d|@- ] --> ", temp->value);
			temp = temp ->levels[level];
		}
		printf(" NULL\n");
    }
}

// Optional: display all levels of the list, by aligning the cells
/*
void display_list_aligned(t_list* list, int level){
	t_cell *temp = list->heads[level];
	t_cell *temp_level1 = list->heads[0];
	printf("[list head_%d @-]--",level);
	if (temp == NULL){
		while (temp_level1!=temp){
			printf("------------");
			temp_level1 = temp_level1->levels[0];
		}
		printf("> NULL\n");
	}
	else{
		while (temp->levels[level]!=NULL){
			while (temp_level1!=temp){
				printf("------------");
				temp_level1 = temp_level1->levels[0];
			}
			printf(">[ %d|@- ] -- ", temp->value);
			temp = temp ->levels[level];

			
		}
	}

	
	
}
*/

// Show all levels in the list 

void display_all(t_list* list){
	for (int i=0; i<list->max_levels;  i++){
		display_level(list, i);
	}
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
		if (current->value > cell->value)
			// break is not always considered a good practice, but with good commenting, it **is** okay.
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