#include <stdio.h>
#include <string.h>

struct date {
	int day;
	int month;
	int year;
}

/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr){
        struct Date *d = (struct date *)malloc(sizeof(struct d));

        if(false){
                //checkStr
        }
        else{ //start copy strings
			strcpy(

        }

        return d;
}

/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date *date_duplicate(Date *d);

/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2);

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d);

int main(int argc, char *argv[]) {
        struct Date *testDay = NULL;
        testDay = date_create("20/10/2017");
        printf("Day : %d",*testDay.day);
        printf("Month : %d",*testDay.month);
        printf("Year: %d",*testDay.year);
}