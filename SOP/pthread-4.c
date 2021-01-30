#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int n;

void funcThread(void *argp) {
     printf("bloqueando...\n");
     sleep(20);
     printf("\ndesbloqueado\n");
}

void calcThread(void *argp) {
     int i;
     sleep(1);
     for (i = 0; i < 10000000; i++) {
         printf("%d\r", i);
     }
}

int main(void) {
     pthread_t t1, t2;
     int rc;
     n = 7;
     rc = pthread_create(&t1, NULL, (void *)funcThread, (void *) "Baiacu");
     rc = pthread_create(&t2, NULL, (void *)calcThread, (void *) "Bagre");
     rc = pthread_join(t1, NULL);
     rc = pthread_join(t2, NULL);
     return 0;
}
