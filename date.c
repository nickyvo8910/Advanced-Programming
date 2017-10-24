#include <stdio.h>
#include <string.h>

type def struct date {
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
        struct Date *d = (struct date *)malloc(sizeof(struct d));

        if(false){
                //checkStr
					//length ==10
					//2 & 5 == '/'
				// d = NULL ???
        }
        else{
			sscanf(datestr, "%d/%d/%d",&d.day,&d.month,&d.year);
			//Copy 0 &1 to d.day			
			//3 &4 to d.month
			// 6789 to d.year
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
	struct Date *newDate = (struct date *)malloc(sizeof(struct d));
	*newDate.day = *d.day;
	*newDate.month = *d.month;
	*newDate.year = *d.year;
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

int main(int argc, char *argv[]) {
        struct Date *testDay = NULL;
        testDay = date_create("20/10/2017");
        printf("Day : %d",*testDay.day);
        printf("Month : %d",*testDay.month);
        printf("Year: %d",*testDay.year);
}