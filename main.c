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

char* scanString() {
	fflush(stdin);
	char* buffer = NULL;
	int length = 0;
	int size = 0;
	int c;

	while ((c = getchar()) != '\n' && c != EOF) {
		if (length + 1 > size) {
			size = size == 0 ? 2 : size * 2;
			buffer = realloc(buffer, size);
		}
		buffer[length++] = (char)c;
	}

	if (length > 0) {
		buffer = realloc(buffer, length + 1);
		buffer[length] = '\0';  // Null-terminate the string
	}

	return buffer;
}


void display_level(ContactStore* list, int level) {
	ContactCell *temp = list->heads[level];
	if (temp == NULL)
		printf("[list head_%d @-]-->NULL\n", level);
	else {
		printf("[list head_%d @-]-->",level);
		while(temp != NULL) {
			printf("[ %s|@-]-->", temp->id);
			temp = temp ->levels[level];
		}
		printf(" NULL\n");
	}
}

void display_list(ContactStore* list){
	for (int i=0; i<4; i++)
		display_level(list, i);
}


int main() {
	ContactStore CONTACTS;
	for (int i = 0; i < 4;i++)
		CONTACTS.heads[i] = NULL;
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
	int choice = 0;
	while (choice != 8) {
		int choice = displayMenu(menu, 9);
		switch (choice) {
			case 0: {
				printf("== Add a contact ==\n");
				printf("First name: ");
				char* firstName = scanString();
				printf("Last name: ");
				char* lastName = scanString();
				createContact(firstName, lastName, &CONTACTS);
				break;
			}
			case 8: {
				return 0;
			}
			default:
				printf("To be implemented...\n");
				break;
		}
	}
	return 0;
}
