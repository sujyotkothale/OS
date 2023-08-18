#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/sem.h>
#include<pthread.h>
sem_t a,b,c;

void *A(void* arg){
 	while(1){
 	 	sem_wait(&a);
 	 	printf("\n\t A");
 	 	sleep(1);
 	 	sem_post(&b);
 	}
}
void *B(void* arg){
 	while(1){
 	 	sem_wait(&b);
 	 	printf("\n B");
 	 	sleep(1);
 	 	sem_post(&a);
 	 	sem_post(&c);
 	}
}
void *C(void* arg){
 	while(1){
 	 	sem_wait(&c);
 	 	printf("\n\t C");
 	 	sleep(1);
 	}
}
int main (int argc, char *argv[])
{
	sem_init(&a,0,1);
	sem_init(&b,0,0);
	sem_init(&c,0,0);
	
	pthread_t P1,P2,P3;
	
	pthread_create(&P1,NULL,A,NULL);
	pthread_create(&P2,NULL,B,NULL);
	pthread_create(&P3,NULL,C,NULL);
	
	pthread_join(P1,NULL);
	pthread_join(P2,NULL);
	pthread_join(P3,NULL);
	
	return 0;
}
