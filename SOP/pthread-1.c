#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void funcThread(void *argp)
{
     sleep(2);
     printf("Alo do filho (pid=%u, thread=%u, arg=%s)\n", getpid(), 
	    pthread_self(), (char *)argp);
     sleep(3);
}

int main(void)
{
     pthread_t t1;
     int rc;
     
     printf("Processo principal (pid=%u, thread=%u)\n", getpid(), 
	    pthread_self());

     rc = pthread_create(&t1, NULL, (void *)funcThread, (void *) "Bacalhau");

     if (rc != 0) {
	  perror("erro na criacao da thread");
	  exit(1);
     }
     printf("Pai (thread=%u) esperando pelo filho (thread=%u)\n", 
	    pthread_self(), t1);

     rc = pthread_join(t1, NULL);

     if (rc != 0) {
	  perror("erro no join");
	  exit(1);
     }
     return 0;
}
