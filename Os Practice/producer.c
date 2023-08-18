#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_t p,q;
int buff[5];
int buffindex = 0;

void *produce(void* arg){
 	for(int i=0;i<10;i++){
 	 	pthread_mutex_lock(&mutex);
 	 	if(buffindex == 5){
 	 	 	pthread_cond_wait(&empty,&mutex);
 	 	}
 	 	buff[buffindex] = 1;
 	 	buffindex++;
 	 	printf("\nProduced : %d",buffindex);
 	 	sleep(1);
 	 	pthread_mutex_unlock(&mutex);;
 	 	pthread_cond_signal(&full);
 	}
}
void *consumer(void* arg){
 	
 	for(int i=0;i<10;i++){
 	 	pthread_mutex_lock(&mutex);
 	 	if(buffindex == 0){
 	 	 	pthread_cond_wait(&full,&mutex);
 	 	}
 	 	buffindex--;
 	 	printf("\nConsumed : %d",buffindex+1);
 	 	sleep(1);
 	 	pthread_mutex_unlock(&mutex);;
 	 	pthread_cond_signal(&empty);
 	}
}
int main (int argc, char *argv[])
{
	pthread_create(&q,NULL,consumer,NULL);
	pthread_create(&p,NULL,produce,NULL);
	
	pthread_join(p,NULL);
	pthread_join(q,NULL);
	return 0;
}
