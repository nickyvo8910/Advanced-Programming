#include <stdio.h>
#include <string.h>

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
void date_destroy(Date *d){}
void to_string(Date *d){
	printf("Day : %d, Month : %d, Year : %d \n",d->day,d->month,d->year);
}

int main(int argc, char *argv[]) {
        Date *testDay = NULL;
        testDay = date_create("20/10/2017");
        to_string(testDay);
        
        Date *dupDate = date_duplicate(testDay);
       	to_string(dupDate);
        
        Date *laterDate = date_create("24/10/2017");
        Date *earlierDate = date_create("10/10/2017");
        printf("Later: %d",date_compare(laterDate,testDay));
        printf("Earlier: %d",date_compare(earlierDate,testDay));
        printf("\n");
        
        Date *ruinedDate = date_create("24/10/2017");
        printf("\nBefore:");
        to_string(ruinedDate);
        date_destroy(ruinedDate);
        printf("\nAfter:");
        to_string(ruinedDate);
}
