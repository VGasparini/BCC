/* Exercicio 6 da lista de pthreads */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#define down(x) sem_wait(x)
#define up(x) sem_post(x)

sem_t mutex;

#define MAX 2000

long n;

void *f1(void *argp)
{
    long i;
    for (i = 0; i < MAX; i++) {
	 down(&mutex);
	 n++; /* r1 <- n ; add r1, 1 ; n <- r1 */
	 up(&mutex);
    }
    pthread_exit(NULL);
}

void *f2(void *argp)
{
    long i;
    for (i = 0; i < MAX; i++) {
	 down(&mutex);
	 n--;
	 up(&mutex);
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t t1, t2;
    int rc;

    n = 0;
    sem_init(&mutex, 0, 1);  /* mutex = 1 */
    rc = pthread_create(&t1, NULL, f1, NULL);   assert(rc == 0);
    rc = pthread_create(&t2, NULL, f2, NULL);   assert(rc == 0);
    rc = pthread_join(t1, NULL);   assert(rc == 0);
    rc = pthread_join(t2, NULL);   assert(rc == 0);
    printf("%ld\n", n);
    return 0;
}
