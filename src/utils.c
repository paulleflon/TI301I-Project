#include "../headers/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char* substr(char* str, int length) {
	int originalLength = strlen(str);
	length = length > originalLength ? originalLength : length;
	char* res = (char*) malloc((length + 1) * sizeof(char));
	int i;
	for (i = 0; i < length; i++)
		res[i] = str[i];
	res[i] = '\0';
	return res;
}