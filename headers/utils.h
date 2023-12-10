#ifndef UTILS_H
#define UTILS_H


typedef struct s_date {
	int day;
	int month;
	int year;
} Date;

typedef struct s_time {
	int hours;
	int minutes;
} Time;

int displayMenu(char** options, int length);
char* scanString();
int isLeapYear(int year);
int isValidDate(int day, int month, int year);
Date* scanDate();
int isValidTime(int hours, int minutes);
Time* scanTime();
char* substr(char* str, int length);
#endif
