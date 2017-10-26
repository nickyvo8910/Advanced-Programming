#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_DATE_STRING_FORMAT 200 //LEAK ???

typedef struct date {
	int day;
	int month;
	int year;
}Date;


/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr){
        Date *d = (Date *)malloc(sizeof(Date));
		int checked =0;
		if(datestr == NULL || datestr =="") d= NULL;
 		else checked =1;
		if(checked == 1)  {
			int dd,mm,yy=0;
			sscanf(datestr, "%d/%d/%d",&dd,&mm,&yy);
			d->day = dd;
			d->month= mm;
			d->year = yy;
		}

        return d;
}

/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date *date_duplicate(Date *d){
	//new date
	Date *newDate = (Date *)malloc(sizeof(Date));
	newDate->day = d->day;
	newDate->month = d->month;
	newDate->year = d->year;
	return newDate;
}

/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2){
	if(date1 ->year != date2 ->year)
		return date1 ->year - date2 ->year;
	if(date1 ->month != date2 ->month)
		return date1 ->month - date2 ->month;
	if(date1 ->day != date2 ->day)
		return date1 ->day - date2 ->day;
	return 0;
}

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d){
	free(d);
}
/*

char* date_to_string(Date *d){
	char *dayStr[5];
	char *monthStr[5];
	char *yearStr[5];
	itoa((*d).day,dayStr,10);// 10 as base10
	itoa((*d).month,monthStr,10);
	itoa((*d).year,yearStr,10);
	
	
	char *rtnStr[MAX_DATE_STRING_FORMAT];
	strcpy(rtnStr, "Day: ");
	strcat(rtnStr,dayStr);
	strcat(rtnStr,", Month: ");
	strcat(rtnStr,monthStr);
	strcat(rtnStr,", Year: ");
	strcat(rtnStr,yearStr);
	return rtnStr;
}*/


/*

int main(int argc, char *argv[]) {
        Date *testDay = NULL;
        testDay = date_create("20/10/2017");
        printf("\n");
        printf(date_to_string(testDay));
        printf("\n");
        
        Date *dupDate = date_duplicate(testDay);
       	printf(date_to_string(dupDate));
       	printf("\n");
        
        Date *laterDate = date_create("24/10/2017");
        Date *earlierDate = date_create("10/10/2017");
        printf("Later: %d",date_compare(laterDate,testDay));
        printf("\n");
        printf("Earlier: %d",date_compare(earlierDate,testDay));
        printf("\n");
        
        Date *ruinedDate = date_create("24/10/2010");
        printf("\nBefore:");
        printf(date_to_string(ruinedDate));
        date_destroy(ruinedDate);
        printf("\nAfter:");
        printf(date_to_string(ruinedDate));
}*/
