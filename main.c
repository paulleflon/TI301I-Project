#include <stdio.h>
#include <stdlib.h>
#include "headers/appointments.h"

int displayMenu(char** options, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d. %s\n", i + 1, options[i]);
	}
	int choice = -1;
	while (choice < 1 || choice > length) {
		printf("Choose your option: ");
		scanf("%d", &choice);
	}
	// At first, `choice` is user-friendly so its range stars from 1, but the value we actually need
	// from the function is the index of the chosen option, hence the -1.
	return choice - 1;
}

int main() {
	ContactStore CONTACTS = {
		 ontac
		 4
	 };
	char* menu[9] = {
			"Add contact",
			"Add appointment",
			"Search contact",
			"View contact appointments",
			"Delete appointment",
			"Save appointments",
			"Load save",
			"Performance trace",
			"Exit"
	};
	displayMenu(menu, 9);
	return 0;
}
