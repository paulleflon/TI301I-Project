#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "headers/cell.h"
#include "headers/list.h"
#include "headers/timer.h"

/**
 * Demonstration of part 1 functions
 */
void part1_demo() {
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
}

/**
 * Demonstration of part 2 functions
 */
void part2_search_demo() {
	t_list *lst = create_sample_list(3);
	display_list_aligned(lst);
	printf("Is 1 in level 1 ? - %s\n", search_list_level(lst, 1, 4) ? "Yes" : "No");
	printf("Is 1 in the list ? - %s\n", search_list(lst, 4) ? "Yes" : "No");
}

void part2_comparison() {
	t_list* sample;
	int i, j, k, max;
	for (i = 5; i <= 14; i++) {
		max = pow(2, i) - 1;
		printf("=== For n = %d ===\n", i);
		printf("Level 0 search | Multi-level search\n");
		sample = create_sample_list(i);
		for (j = 1000; j <= 100000; j*= 10) {
			printf("%d searches: ", j);
			startTimer();
			for (k = 0; k < j; k++)
				search_list_level(sample, 0, (int)rand() % max + 1);
			stopTimer();
			printf("%s | ", getTimeAsString());
			startTimer();
			for (k = 0; k < j; k++)
				search_list(sample, (int)rand() % max + 1);
			stopTimer();
			printf("%s\n", getTimeAsString());
		}
	}
}

int main() {
	srand(time(NULL));
	part2_comparison();
}
