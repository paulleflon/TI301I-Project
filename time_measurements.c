#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "headers/list.h"
#include "headers/timer.h"

#define TEST_FROM 1
#define TEST_UNTIL 16
#define SEARCH_ATTEMPTS 10000
int main() {
	// Disables buffering for printf. In other words, updates the output for each print statement, rather than each line
	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(NULL));
	t_list *lst;
	double lvl10_time,
			multilevel_time;
	int max_value,
		i, j;
	FILE *results_file = fopen("times.csv", "w");
	fprintf(results_file, "N,Duration for %d searches with Level 0 search (ms),Duration for %d searches with Multilevel search (ms)\n", SEARCH_ATTEMPTS, SEARCH_ATTEMPTS);
	for (i = TEST_FROM; i <= TEST_UNTIL; i++) {
		printf("Timing for n = %d", i);
		lst = create_sample_list(i);
		// This is done after the generation of the sample list just to have an idea of how long it takes to generate it
		// But this information is not what we're searching for in this algorithm, so we don't display more verbose.
		printf(": ");
		max_value = pow(2, i) - 1;
		startTimer();
		for (j = 0; j < SEARCH_ATTEMPTS; j++) {
			search_list_level(lst, 0, rand() % max_value);
		}
		stopTimer();
		lvl10_time = getMilliseconds();
		printf("%f", lvl10_time);
		startTimer();
		for (j = 0; j < SEARCH_ATTEMPTS; j++) {
			search_list(lst, rand() % max_value);
		}
		stopTimer();
		multilevel_time = getMilliseconds();
		printf(" - %f\n", multilevel_time);
		fprintf(results_file, "%d,%f,%f\n", i, lvl10_time, multilevel_time);
	}
	fclose(results_file);
	return 0;
}