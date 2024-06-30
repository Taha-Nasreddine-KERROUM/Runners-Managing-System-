#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define H 10

typedef struct {
    int hour;
    int minute;
    int second;
} mytime;

typedef struct {
    char name[100];
    mytime start;
    mytime raceTM;
    mytime end;
} runner;

int toSec(mytime t){
    return t.hour * 36e2 + t.minute * 6E1 + t.second;
}

mytime toHour(int s){
    mytime t;
    t.hour = s / 3600;
    s %= 3600;
    t.minute = s / 60;
    s %= 60;
    t.second = s;
    return t;
}

// or if you wanna look cool
/*********
mytime toHour(int s) {
    return (mytime) { s / 3600, (s %= 3600) / 60, s % 60 };
}
******/

mytime subtract( mytime big, mytime lil ){
    return toHour( toSec(big) - toSec(lil) );
}

void readTime ( mytime *t ){
    printf("hour: ");
    scanf("%d", &t->hour);
    printf("minute: ");
    scanf("%d", &t->minute);
    printf("second: ");
    scanf("%d", &t->second);
}

void readRunner ( runner *r, int size ){
    for ( runner *i = r; i < r + size; ++i ){
        printf("\nrunner %d:\n"
               "start:\n", i-r+1);
        readTime(&i->start);
        puts("end:");
        readTime(&i->end);
    }
}

void raceTimeCalc ( runner *r, int size ){
    for ( int i = 0; i < size; ++i )
        r[i].raceTM = subtract( r[i].end, r[i].start );
}

bool tmcmp ( runner one, runner two ){
    return toSec(one.raceTM) > toSec(two.raceTM);
}

void swap ( runner *one, runner *two ){
    runner temp = *one;
    *one = *two;
    *two = temp;
}

void bubbleSort( runner *r, int size ){
    for( int i = 0; i < size-1; ++i )
        for( int j = 0; j < size-1; ++j )
            if ( tmcmp( r[j], r[j+1] ) )
                swap( r+j, r+j+1 );
}

void displayTm ( mytime t ){
    printf("%02d:%02d:%02d\n", t.hour, t.minute, t.second);
}

void displayRn ( runner *r, int size ){
    for ( runner *i = r; i < r + size; ++i ){
        printf("\nclass %d:\n"
               "start: ", i+1-r);
        displayTm(i->start);
        printf("end: ");
        displayTm(i->end);
        printf("run time: ");
        displayTm(i->raceTM);
    }
}

void main(void){
    runner rn[10];
    int size;
    
    printf("how many nighas are racin'? ");
    scanf("%d", &size);
    
    readRunner(rn, size);
    raceTimeCalc(rn, size);
    bubbleSort(rn, size);
    displayRn(rn, size);
}
