#include <stdio.h>
#include <stdlib.h>
#include "headers/appointments.h"
#include "headers/utils.h"

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
	createContact("ben", "leflon",&CONTACTS);
	createContact("paul", "leflon",&CONTACTS);
	createContact("oli", "leflon",&CONTACTS);
	createContact("adele", "chamoux",&CONTACTS);
	createContact("chamoux", "chamoux",&CONTACTS);
	createContact("iri", "rasolo",&CONTACTS);
	display_list(&CONTACTS);
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
				printf("== Successfully added a new contact ==\n");
				break;
			}
			case 1: {
				printf("== Add an appointment ==\n");
				printf("Contact Id: ");
				char* id = scanString();
				ContactCell* cell = searchContactById(&CONTACTS, id);
				if (cell == NULL)  {
					printf("There is no contact with id: %s\n", id);
					break;
				}
				printf("Please enter the reason of the appointment: ");
				char* reason = scanString();
				printf("Please enter the date of the appointment:\n");
				Date* date = scanDate();
				printf("Please enter the time of the appointment:\n");
				Time* time = scanTime();
				printf("Please enter the duration of the appointment:\n");
				Time* dur = scanTime();
				Appointment* appointment = createAppointment(date, time, dur, reason);
				insertAppointmentInList(cell->contact->appointments, appointment);
				printf("== Successfully created a new appointment ==\n");
				break;
			}
			case 2: {
				printf("== Search contacts ==\n");
				printf("Query: ");
				char* query = scanString();
				int length = 0;
				ContactCell** results = searchContactsByQuery(&CONTACTS, query, &length);
				if (length == 0) {
					printf("There is no contact whose id starts with \"%s\"\n", query);
					break;
				}
				printf("Found %d contacts:\n", length);
				for(int i = 0; i < length;i++) {
					printf("%s %s (%s)", results[i]->contact->firstName, results[i]->contact->lastName, results[i]->id);
					if (i != length - 1)
						printf(", ");
				}
				printf("\n");
				break;
			}
			case 3: {
				printf("== View contact's appointments ==\n");
				printf("Contact Id:");
				char *id = scanString();
				ContactCell* cell = searchContactById(&CONTACTS, id);
				if (cell == NULL)  {
					printf("There is no contact with id: %s\n", id);
					break;
				}
				displayAppointments(cell->contact->appointments);
				break;
			}
			case 4: {
				printf("== Delete contact's apppointment ==\n");
				printf("Contact Id:");
				char *id = scanString();
				ContactCell* cell = searchContactById(&CONTACTS, id);
				if (cell == NULL)  {
					printf("There is no contact with id: %s\n", id);
					break;
				}
				printf("Appointment Index:");
				int i;
				scanf("%d", &i);
				int success = removeAppointmentByIndex(cell->contact->appointments, i);
				if (success)
					printf("== Sucessfully deleted appointment %d ==\n", i);
				else
					printf("== No appointment with id %d ==\n", i);
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
