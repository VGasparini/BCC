/* 
Vinicius Gasparini
Ex 1 - Programa para mostrar sincronizacao e concorrencia de threads. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

#define down(x) sem_wait(x)
#define up(x) sem_post(x)

sem_t s1, s2, s3;

int s1_val = 0;
int s2_val = 0;
int s3_val = 0;

int s1_val_ended = 0xfff;
int s2_val_ended = 0xfff;
int s3_val_ended = 0xfff;

void rand_wait(void)
{
#define RMAX 10000
    long r;
    while ((r = random() % RMAX) != 171)
        ;
}

void *A(void *argp)
{
    {
        rand_wait();
        down(&s1);
        printf("O");
        up(&s1);
        up(&s3);

        pthread_exit(NULL);
    }
}

void *B(void *argp)
{
    {
        rand_wait();
        printf("CA");
        up(&s1);
        down(&s2);
        down(&s3);
        down(&s1);
        printf("!\n");

        rand_wait();
        sem_getvalue(&s1, &s1_val_ended);
        sem_getvalue(&s2, &s2_val_ended);
        sem_getvalue(&s3, &s3_val_ended);

        pthread_exit(NULL);
    }
}

void *C(void *argp)
{
    {
        rand_wait();
        down(&s1);
        printf("S");
        up(&s1);
        up(&s2);

        pthread_exit(NULL);
    }
}

int main(void)
{
    pthread_t t1, t2, t3;
    int rc, i;

    sem_init(&s1, 0, s1_val);
    sem_init(&s2, 0, s2_val);
    sem_init(&s3, 0, s3_val);

    rc = pthread_create(&t1, NULL, A, NULL);
    assert(rc == 0);
    rc = pthread_create(&t2, NULL, B, NULL);
    assert(rc == 0);
    rc = pthread_create(&t3, NULL, C, NULL);
    assert(rc == 0);

    rc = pthread_join(t1, NULL);
    assert(rc == 0);
    rc = pthread_join(t2, NULL);
    assert(rc == 0);
    rc = pthread_join(t3, NULL);
    assert(rc == 0);

    assert(s1_val == s1_val_ended);
    assert(s2_val == s2_val_ended);
    assert(s3_val == s3_val_ended);

    return 0;
}
