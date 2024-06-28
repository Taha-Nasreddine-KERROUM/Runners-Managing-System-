#include <stdio.h>
#include <stdlib.h>
#define u 100

typedef struct {
    char nam[u];
    double min;
    double sec;
} tik;

double toSec ( tik r ) {
    return r.min * 60 + r.sec;
}

void print ( tik *r, int n ) {
    for ( tik *p = r; p < r + n; ++p )
        printf(" at %ld class comes %s with %.2lfm %.2lfs\n", p - r + 2, p->nam, p->min, p->sec);
}

void shell ( tik *r, int n ) {
    int h;
    for (h = 0; h <= n; h = h * 3 + 1);
    for (h = (h - 1) / 3; h > 0; h = (h - 1) / 3)
        for (int i = h; i < n; i++) {
            tik temp = r[i], *j;
            for (j = r + i; j >= r + h && toSec( *(j - h) ) > toSec(temp); j -= h)
                *j = *(j - h);
            *j = temp;
        }
}

void read ( tik *r, int n ) {
    for ( tik *p = r; p < r + n; ++p ) {
        printf(" runner's %ld name: ", p - r);
        fgets( p->nam, u, stdin );
        printf(" his minutes: ", p - r);
        scanf("%lf", &p->min);
        printf(" his secs: ", p - r);
        scanf("%lf%*c", &p->sec);
    }
}

int main()
{
    tik *r;
    int n;
    printf(" how many runners did you have: ");
    scanf("%d%*c", &n);
    r = ( tik* ) malloc ( n * sizeof( tik ) );
    read( r, n );
    shell( r, n );
    printf(" the record holder is %s with %.2lfm %.2lfs\n", r->nam, r->min, r->sec);
    printf(" the rest are:\n");
    print( r + 1, n - 1 );
    
    free( r );
    r = NULL;
    return 0;
}
