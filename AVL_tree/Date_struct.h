#ifndef DATE_STRUCT
#define DATE_STRUCT
#include "libraries.h"

struct Date
{
	int day = 0;
	int month = 0;
	int year = 0;
};

bool LeapYear(int year)
{
	if (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0)
		return true;
	else return false;
}

int DayInMonth(int month, int year)
{
	int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (LeapYear(year)) days[2] = 29;
	return days[month];
}

bool CorrectDate(int day, int month, int year)
{
	if ((day < 1 || day>31) || (month < 1 || month>12) || year < 1)
	{
		return false;
	}
	else if (day <= DayInMonth(month, year))
		return true;
	else return false;
}

void setDate(Date& date, int day, int month, int year)
{
	date.day = day;
	date.month = month;
	date.year = year;

}


#endif