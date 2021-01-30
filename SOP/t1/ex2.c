/* 
Vinicius Gasparini
Ex 2 - Programa para simular uma corrida em busca de determinado valor
        em matrizes sorteadas utilizando threads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "matrix.h"

#define TRUE 1
#define FALSE 0

#define MAX_THREADS 4
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define FOR(x, n) for (int x = 0; (x) < (int)n; (x)++)
#define REVERSE(x, n) for (int x = (int)n - 1; (x) >= 0; (x)--)

pthread_barrier_t barrier_search_race;
pthread_mutex_t mutex_winner;
pthread_mutex_t mutex_race;
pthread_cond_t cond_race;

int debbug = FALSE;

int n, m;
int is_thread_winner;
int score[MAX_THREADS];
int max_score;

typedef struct args
{
    int id;
    int initial_quadrant;
    int value;
} Thread_args;

void *thread_func(void *argp)
{
    int finished = FALSE;
    Thread_args *thread_info = (Thread_args *)argp;

    if (debbug)
        printf("\nThread %d iniciada\n", thread_info->id);

    int **matrix = allocate_matrix(n, m);
    init_matrix(matrix, n, m);
    shuffle_matrix(matrix, n, m);

    if (debbug > 1)
        print_matrix(matrix, n, m);

    pthread_barrier_wait(&barrier_search_race);
    if (debbug)
        printf("\nBusca por [%d] na thread %d iniciada\n", thread_info->value, thread_info->id);

    switch (thread_info->initial_quadrant - 1)
    {
    case 0:
        FOR(row, m)
        {
            if (finished)
                break;
            FOR(column, n)
            {
                if (finished)
                    break;
                if (debbug > 1)
                    printf("[%d] %d -> ", thread_info->id, matrix[row][column]);
                if (matrix[row][column] == thread_info->value)
                {
                    pthread_mutex_lock(&mutex_winner);
                    if (is_thread_winner)
                    {
                        score[thread_info->id - 1]++;
                        if (debbug > 1)
                            printf("Thread %d diz: Ganhei!\n", thread_info->id);
                        is_thread_winner = FALSE;
                        max_score = MAX(max_score, score[thread_info->id - 1]);
                    }
                    pthread_mutex_unlock(&mutex_winner);
                    finished = TRUE;
                }
            }
        }
        break;
    case 1:
        REVERSE(row, m)
        {
            if (finished)
                break;
            FOR(column, n)
            {
                if (finished)
                    break;
                if (debbug > 1)
                    printf("[%d] %d -> ", thread_info->id, matrix[row][column]);
                if (matrix[row][column] == thread_info->value)
                {
                    pthread_mutex_lock(&mutex_winner);
                    if (is_thread_winner)
                    {
                        score[thread_info->id - 1]++;
                        if (debbug > 1)
                            printf("Thread %d diz: Ganhei!\n", thread_info->id);
                        is_thread_winner = FALSE;
                        max_score = MAX(max_score, score[thread_info->id - 1]);
                    }
                    pthread_mutex_unlock(&mutex_winner);
                    finished = TRUE;
                }
            }
        }
        break;
    case 2:
        FOR(row, m)
        {
            if (finished)
                break;
            REVERSE(column, n)
            {
                if (finished)
                    break;
                if (debbug > 1)
                    printf("[%d] %d -> ", thread_info->id, matrix[row][column]);
                if (matrix[row][column] == thread_info->value)
                {
                    pthread_mutex_lock(&mutex_winner);
                    if (is_thread_winner)
                    {
                        score[thread_info->id - 1]++;
                        if (debbug > 1)
                            printf("Thread %d diz: Ganhei!\n", thread_info->id);
                        is_thread_winner = FALSE;
                        max_score = MAX(max_score, score[thread_info->id - 1]);
                    }
                    pthread_mutex_unlock(&mutex_winner);
                    finished = TRUE;
                }
            }
        }
        break;
    case 3:
        REVERSE(row, m)
        {
            if (finished)
                break;
            REVERSE(column, n)
            {
                if (finished)
                    break;
                if (debbug > 1)
                    printf("[%d] %d -> ", thread_info->id, matrix[row][column]);
                if (matrix[row][column] == thread_info->value)
                {
                    pthread_mutex_lock(&mutex_winner);
                    if (is_thread_winner)
                    {
                        score[thread_info->id - 1]++;
                        if (debbug > 1)
                            printf("Thread %d diz: Ganhei!\n", thread_info->id);
                        is_thread_winner = FALSE;
                        max_score = MAX(max_score, score[thread_info->id - 1]);
                    }
                    pthread_mutex_unlock(&mutex_winner);
                    finished = TRUE;
                }
            }
        }
        break;
    }

    pthread_mutex_lock(&mutex_race);
    if (debbug)
        printf("Thread %d concluida\n", thread_info->id);
    free_matrix(matrix, n, m);
    pthread_cond_signal(&cond_race);
    pthread_mutex_unlock(&mutex_race);
    pthread_exit(NULL);
}

void show_round_score(void)
{
    int i;
    printf("Score ate aqui: ");
    for (i = 0; i < MAX_THREADS; i++)
    {
        printf(" %d", score[i]);
    }
    printf("\n");
}

void show_final_score(void)
{
    int i;
    printf("\n-----------------------------------\n");
    for (i = 0; i < MAX_THREADS; i++)
        printf("thread\t%d =>\t\t%d vitorias\n", i + 1, score[i]);
    printf("-----------------------------------\n");
    printf("Thread(s) vencedora(s):");
    for (i = 0; i < MAX_THREADS; i++)
    {
        if (score[i] == max_score)
            printf(" %d ", i + 1);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int i, k, rc;

    m = atoi(argv[1]);
    n = atoi(argv[2]);
    k = atoi(argv[3]);
    if (argv[4] != NULL)
        debbug = atoi(argv[4]);
    pthread_t t[MAX_THREADS];

    for (int rod = 0; rod < k; rod++)
    {
        pthread_mutex_init(&mutex_winner, NULL);
        pthread_mutex_init(&mutex_race, NULL);
        pthread_cond_init(&cond_race, NULL);

        if (debbug)
            printf("-== Rodada %d! ==-\n", rod + 1);
        int value_to_find = random() % (n * m) + 1;
        is_thread_winner = TRUE;

        rc = pthread_barrier_init(&barrier_search_race, NULL, MAX_THREADS);
        assert(rc == 0);
        for (i = 1; i <= MAX_THREADS; i++)
        {
            Thread_args *thread_info = (Thread_args *)malloc(sizeof(Thread_args));

            thread_info->id = i;
            thread_info->initial_quadrant = i;
            thread_info->value = value_to_find;

            rc = pthread_create(&t[i - 1], NULL, thread_func, (void *)thread_info);
            assert(rc == 0);
        }

        for (i = 0; i < MAX_THREADS; i++)
        {
            rc = pthread_join(t[i], NULL);
            assert(rc == 0);
        }

        rc = pthread_mutex_lock(&mutex_race);
        assert(rc == 0);
        while (is_thread_winner)
        {
            rc = pthread_cond_wait(&cond_race, &mutex_race);
            assert(rc == 0);
        }
        if (debbug)
            show_round_score();
        rc = pthread_mutex_unlock(&mutex_race);
        assert(rc == 0);
    }

    show_final_score();

    rc = pthread_barrier_destroy(&barrier_search_race);
    assert(rc == 0);
    rc = pthread_cond_destroy(&cond_race);
    assert(rc == 0);
    rc = pthread_mutex_destroy(&mutex_winner);
    assert(rc == 0);
    rc = pthread_mutex_destroy(&mutex_race);
    assert(rc == 0);
    return 0;
}
