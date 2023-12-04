#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../headers/appointments.h"

Contact* createContact(char *name, char *lastname, ContactStore* calendar) {
	//region 1. Contact creation
	Contact* contact = (Contact*) malloc(sizeof(Contact));
	contact->firstName = name;
	contact->lastName = lastname;
	contact->appointments = (AppointmentList*) malloc(sizeof(AppointmentList));
	contact->appointments->head = NULL;
	//endregion
	//region 2. ContactCell creation
	ContactCell* cell = (ContactCell*) malloc(sizeof(ContactCell));
	cell->contact = contact;
	char* lowerName = (char*) malloc(sizeof(*name));
	char* lowerLastName = (char*) malloc(sizeof(*lastname));
	int i = 0;
	while (name[i] != '\0') {
		lowerName[i] = (char)tolower(name[i]);
		i++;
	}
	while (lastname[i] != '\0') {
		lowerLastName[i] = (char)tolower(lastname[i]);
		i++;
	}
	sprintf(cell->id, "%s_%s", lowerLastName, lowerName);
	// The nbLevels and level fields will be determined at insertion.
	//endregion
	//region Insertion in calendar
	ContactCell* current = calendar->heads[0];
	
	if (current == NULL) {
		for (i = 0; i < 4; i++)
			calendar->heads[i] = current;
	} else {
		 while(strcmp(cell->id, current->id))
	}
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

