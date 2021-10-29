#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t S;
sem_t wrt;

int COUNTING_NUMBER = 100;

int cur_count = 0;
int readcount = 0;

void* writer(void* cur_writer)
{
	int i;
	for(i=0;i<COUNTING_NUMBER;i++) {
		usleep(100000);
		sem_wait(&wrt);	//writer semaphore
		cur_count = i;
		printf("The most recent writer id:\t[%d], count:\t[%d]\n", (*((int*)cur_writer)), cur_count);
		sem_post(&wrt);
	}
}
void* reader(void* cur_reader)
{
	int i;
	for(i=0; i<COUNTING_NUMBER; i++) {
		usleep(30000);
		sem_wait(&S);
		readcount++;	//count the number of reader thread
		if (readcount == 1) {
			sem_wait(&wrt); 
		}
		sem_post(&S);
	
		sem_wait(&S);
		readcount--;
		//unbounded waiting until readcount == 0
		if (readcount == 0) {
			sem_post(&wrt); 
		}
		sem_post(&S);
	}
}

int main()
{

	pthread_t read[2], write[5];
	sem_init(&S,0, 1);
	sem_init(&wrt, 0, 1);
	
	int rd_id[2] = {1,2};
	int wrt_id[5] = {1,2,3,4,5}; 

	for (int i = 0; i < 2; i++) {
		pthread_create(&read[i], NULL, (void*)reader, (void*)&rd_id[i]);
	}
	for (int i = 0; i < 5; i++) {
		pthread_create(&write[i], NULL, (void*)writer, (void*)&wrt_id[i]);
	}

	for (int i = 0; i < 2; i++) {
		pthread_join(read[i], NULL);
	}
	for (int i = 0; i < 5; i++) {
		pthread_join(write[i], NULL);
	}

	sem_destroy(&S);
	sem_destroy(&wrt);

	return 0;

}
