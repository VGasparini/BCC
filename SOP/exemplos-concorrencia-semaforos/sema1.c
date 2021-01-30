/* Programa para mostrar sincronizacao de threads. O programa deveria
 *  imprimir "SOP", mas isso nem sempre ocorre.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#define down(x) sem_wait(x)
#define up(x) sem_post(x)

sem_t sO, sP;

void rand_wait(void)
{
#define RMAX 1000000
     long r;
     while ((r = random() % RMAX) != 171)
	  ;
}

void *S(void *argp)
{
     rand_wait();
     printf("S");
     pthread_exit(NULL);
}

void *O(void *argp)
{
     rand_wait();
     printf("O");
     pthread_exit(NULL);
}

void *P(void *argp)
{
     rand_wait();
     printf("P");
     pthread_exit(NULL);
}

int main(void)
{
     pthread_t t1, t2, t3;
     int rc;
     
     sem_init(&sO, 0, 0);
     sem_init(&sP, 0, 0);
     rc = pthread_create(&t1, NULL, S, NULL);   assert(rc == 0);
     rc = pthread_create(&t2, NULL, O, NULL);   assert(rc == 0);
     rc = pthread_create(&t3, NULL, P, NULL);   assert(rc == 0);
     rc = pthread_join(t1, NULL);   assert(rc == 0);
     rc = pthread_join(t2, NULL);   assert(rc == 0);
     rc = pthread_join(t3, NULL);   assert(rc == 0);
     putchar('\n');
     return 0;
}
