#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    /*METS TON CODE QUE TU VEUX TIMER*/
    gettimeofday(&stop, NULL);
    
    printf("\n%lu\n", stop.tv_usec - start.tv_usec);
    return 0;
}