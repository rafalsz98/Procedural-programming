#pragma once

//#define DEBUG

#define PRINT_COLS 3
#define RESFILENAME "out.txt"

#define LOTTOMAX 50
#define MAXBETS 6

#define PESEL_LENGTH 11

#define ALLOCPLAYER 4
#define ALLOCBET 2

#define MAXNAME 31

#define SWIFTLENGTH 11
#define IBANLENGTH 28

typedef enum {MALE, FEMALE} SexType;
typedef enum {mon, tue, wed, thu, fri, sat, sun} DayNames;
typedef enum {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec} MonthNames;

typedef struct {
	char Swift[SWIFTLENGTH];
	char IBan[IBANLENGTH];
} BankInfo;

typedef struct {
	int day;
	int year;
	DayNames weekDay;
	MonthNames monthName;
} Date;

typedef struct {
	char pFirstName[MAXNAME];
	char pLastName[MAXNAME];
	SexType pSex;
	BankInfo bankInfo;
	int hour;
	int minute;
	Date pDate;
	char pesel[PESEL_LENGTH];
	int** betsArray;
	int betsSize;
} Player;