/* Exercicio 6 da lista de pthreads */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX 2000

long n, lock = 0;

void *f1(void *argp)
{
    long i;
    for (i = 0; i < MAX; i++) {
	 while (lock == 1)
	      ;
	 lock = 1;
	 n++; /* r1 <- n ; add r1, 1 ; n <- r1 */
	 lock = 0;
    }
    pthread_exit(NULL);
}

void *f2(void *argp)
{
    long i;
    for (i = 0; i < MAX; i++) {
	 while (lock == 1)
	      ;
	 lock = 1;
	 n--;
	 lock = 0;
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t t1, t2;
    int rc;

    n = 0;
    rc = pthread_create(&t1, NULL, f1, NULL);   assert(rc == 0);
    rc = pthread_create(&t2, NULL, f2, NULL);   assert(rc == 0);
    rc = pthread_join(t1, NULL);   assert(rc == 0);
    rc = pthread_join(t2, NULL);   assert(rc == 0);
    printf("%ld\n", n);
    return 0;
}
