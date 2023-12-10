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

int isLeapYear(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int isValidDate(int day, int month, int year) {
	if (year < 0 || month < 1 || month > 12 || day < 1) {
		return 0; // Invalid date
	}

	int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// Update days in February for a leap year
	if (isLeapYear(year)) {
		daysInMonth[2] = 29;
	}

	return (day <= daysInMonth[month]);
}

// Function to scan date in the format DD/MM/YYYY
Date* scanDate() {
	int day, month, year;
	do {
		printf("Enter date (DD/MM/YYYY): ");
		scanf("%d/%d/%d", &day, &month, &year);
		if (!isValidDate(day, month, year)) {
			printf("Invalid date. Please enter a valid date.\n");
		}
	} while (!isValidDate(day, month, year));
	Date* date = (Date*)malloc(sizeof (Date));
	date->day = day;
	date->month = month;
	date->year = year;
	return date;
}

int isValidTime(int hours, int minutes) {
	return (hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60);
}

Time* scanTime() {
	int hours, minutes;
	do {
		printf("Enter time (HH:MM): ");
		scanf("%d:%d", &hours, &minutes);
		if (!isValidTime(hours, minutes)) {
			printf("Invalid time. Please enter a valid time.\n");
		}
	} while (!isValidTime(hours, minutes));
	Time* time = (Time*)malloc(sizeof(Time));
	time->hours = hours;
	time->minutes = minutes;
	return time;
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
