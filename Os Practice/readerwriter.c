#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_t r[5],w;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wri = PTHREAD_MUTEX_INITIALIZER;
int readercount = 0;

void *reader(void *arg){
 	for (int i = 0; i < 5; i += 1)
 	{
 		pthread_mutex_lock(&mutex);
 	if(readercount == 0){
 	 	pthread_mutex_lock(&wri);
 	}
 	printf("\nReading %d",readercount++);
 	pthread_mutex_unlock(&mutex);
 	sleep(1);
 	pthread_mutex_lock(&mutex);
 	readercount--;
 	if(readercount == 0){
 	 	pthread_mutex_unlock(&wri);
 	}
 	pthread_mutex_unlock(&mutex);
 	printf("\nreader left");
 	}
}
void *writer(void* arg){
 	
 	for (int i = 0; i < 3; i += 1)
 	{
 		pthread_mutex_lock(&wri);
 		
 		printf("\n\t writing..");
 		sleep(1);
 		pthread_mutex_unlock(&wri);
 		
 	}
}
int main (int argc, char *argv[])
{
	for (int i = 0; i < 5; i += 1)
	{
		pthread_create(&(r[i]),NULL,reader,NULL);
	}
	pthread_create(&w,NULL,writer,NULL);
	for (int i = 0; i < 5; i += 1)
	{
		pthread_join((r[i]),NULL);
	}
	pthread_join(w,NULL);
	return 0;
}

