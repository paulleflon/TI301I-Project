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


// Display all the cells in the list for a given level
void display_list(t_list* list, int level) {
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
		display_list(list, i);
	}
}


//  Insert a level cell in the list, at the right place, so that the list remains sorted in ascending order 
/*void sorted_insert(t_list* list){
}
*/
/* For this last function, it is possible to make a 'simple' insertion at each level, starting
from the beginning of the list, but it is possible to be more efficient - it's up to you
to work out how. 
*/