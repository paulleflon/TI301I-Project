#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../headers/appointments.h"

Contact* createContact(char *firstname, char *lastname, ContactStore* calendar) {
	//region 1. Contact creation
	Contact* contact = (Contact*) malloc(sizeof(Contact));
	contact->firstName = firstname;
	contact->lastName = lastname;
	contact->appointments = (AppointmentList*) malloc(sizeof(AppointmentList));
	contact->appointments->head = NULL;
	//endregion
	//region 2. ContactCell creation
	ContactCell* newCell = (ContactCell*) malloc(sizeof(ContactCell));
	newCell->contact = contact;
	char* lowerName = (char*) malloc(sizeof(*firstname));
	char* lowerLastName = (char*) malloc(sizeof(*lastname));
	int i = 0;
	while (firstname[i] != '\0') {
		lowerName[i] = (char)tolower(firstname[i]);
		i++;
	}
	i = 0;
	while (lastname[i] != '\0') {
		lowerLastName[i] = (char)tolower(lastname[i]);
		i++;
	}
	size_t length = strlen(lowerLastName) + strlen(lowerName) + 2;
	newCell->id = (char*) malloc(length * sizeof(char));
	sprintf(newCell->id, "%s_%s", lowerLastName, lowerName);
	newCell->nbLevels = -1;
	//endregion
	//region 3. Insertion in calendar
	//region 3.a Edge case: Empty list
	if (calendar->heads[0] == NULL) {
		newCell->nbLevels = 4;
		newCell->levels = (ContactCell**) malloc(4 * sizeof(ContactCell*));
		for (i = 0; i < 4; i++) {
			newCell->levels[i] = NULL;
			calendar->heads[i] = newCell;
		}
		return contact;
	}
	//endregion
	//region 3.b Edge case of head insertion
	if (strcmp(newCell->id, calendar->heads[0]->id) < 0) {
		newCell->nbLevels = 4;
		newCell->levels = (ContactCell **) malloc(4 * sizeof(ContactCell *));
		int levels = 1;
		if (newCell->id[0] != calendar->heads[3]->id[0])
			levels = 4;
		else if (calendar->heads[2]->id[1] != newCell->id[1])
			levels = 3;
		else if (calendar->heads[1]->id[2] != newCell->id[2])
			levels = 2;
		for (i = 0; i < 4; i++) {
			if (i < levels)
				 newCell->levels[i] = calendar->heads[i];
			calendar->heads[i] = newCell;
		}
		return contact;
	}
	//endregion
	//region 3.c General Case
	ContactCell* current = NULL;
	current = calendar->heads[0];
	while (current->levels[0] != NULL && strcmp(current->levels[0]->id, newCell->id) < 0)
		current = current->levels[0];
	int levels = 1;
	if (newCell->id[0] != current->id[0])
		levels = 4;
	else if (current->id[1] != newCell->id[1])
		levels = 3;
	else if (current->id[2] != newCell->id[2])
		levels = 2;
	newCell->nbLevels = levels;
	newCell->levels = (ContactCell**) malloc(levels * sizeof(ContactCell*));
	for (i = 0; i < levels; i++) {
		current = calendar->heads[i];
		while (current->levels[i] != NULL && strcmp(current->id, newCell->id) < 0 && strcmp(current->levels[i]->id, newCell->id) < 0)
			current = current->levels[i];
		newCell->levels[i] = current->levels[i];
		current->levels[i] = newCell;
	}
	// Now, we might need to remove the next cell from certain levels
	if (levels > 1 && newCell->levels[1]
		&& newCell->levels[1]->id[0] == newCell->id[0]
		&& newCell->levels[1]->id[1] == newCell->id[1]
		&& newCell->levels[1]->id[2] == newCell->id[2])
		newCell->levels[1] = newCell->levels[1]->levels[1];

	if (levels > 2 && newCell->levels[2]
		&& newCell->levels[2]->id[0] == newCell->id[0]
		&& newCell->levels[2]->id[1] == newCell->id[1])
		newCell->levels[2] = newCell->levels[2]->levels[2];

	if (levels > 3 && newCell->levels[2] && newCell->levels[3]->id[0] == newCell->id[0])
		newCell->levels[3] = newCell->levels[3]->levels[3];
	//endregion
	//endregion
	return contact;
}
Appointment* createAppointment(Date* date, Time* time, Time* duration, char* reason) {
	Appointment* appointment = (Appointment*) malloc(sizeof(Appointment));
	appointment->date = date;
	appointment->time = time;
	appointment->duration = duration;
	appointment->reason = reason;
	return appointment;
}

AppointmentListCell* createAppointmentListCell(Appointment* appointment) {
	AppointmentListCell* cell = (AppointmentListCell*) malloc(sizeof(AppointmentListCell));
	cell->value = appointment;
	cell->next = NULL;
	return cell;
}

void insertAppointmentInList(AppointmentList* list, Appointment* appointment) {
	AppointmentListCell* cell = createAppointmentListCell(appointment);
	cell->next = list->head;
	list->head = cell;
}

void removeAppointmentFromList(AppointmentList* list, Appointment* appointment) {
	if (list->head == NULL)
		return; // List is empty, nothing to delete.

	AppointmentListCell *current = list->head,
						*prev = NULL;
	if (current->value == appointment) {
		list->head = current->next;
		free(current->value);
		free(current);
		return;
	}

	while (current != NULL && current->value != appointment) {
		prev = current;
		current = current->next;
	}

	if (current != NULL) {
		prev->next = current->next;
		free(current->value);
		free(current);
	}
}

void addAppointment(Contact* contact, Appointment* appointment) {
	insertAppointmentInList(contact->appointments, appointment);
}
void deleteAppointment(Contact* contact, Appointment* appointment) {}

