#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int n;

void funcThread(void *argp) {
     printf("filho: n=%d\n", n);
     n = 10;
     printf("filho: n=%d\n", n);
}

int main(void) {
     pthread_t t1;
     int rc;
     n = 7;
     rc = pthread_create(&t1, NULL, (void *)funcThread, (void *) "Bacalhau");
     n = 20;
     printf("pai: n=%d\n", n);
     rc = pthread_join(t1, NULL);
     printf("pai: n=%d\n", n);
     return 0;
}
