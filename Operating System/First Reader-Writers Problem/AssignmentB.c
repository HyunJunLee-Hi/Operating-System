#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdio.h>

#define N 6

int chopstick[N] = {0,1,2,3,4,5};

sem_t mutex[N];

void* philospher(void *num) {
	int *i = (int *)num;
	int right = (*i + 5) % N;
	int left = (*i + 1) % N;
	do {
		usleep(30000);
		//even
		if((*i) % 2 == 0) {
			sem_wait(&mutex[right]);
			sem_wait(&mutex[left]);

		}
		//odd
		else {
			sem_wait(&mutex[left]);
			sem_wait(&mutex[right]);
		}
		printf("%d is eating\n", *i);

		sem_post(&mutex[right]);
		sem_post(&mutex[left]);

		printf("%d is thinking\n" , *i);
		
	}while(1);
}

int main()
{
	int i;
	pthread_t thread_id[N];

	for(i=0; i<N; i++) {
		sem_init(&mutex[i], 0, 1);
	}

	for(i=0; i<N; i++) {
		pthread_create(&thread_id[i], NULL, philospher, (void *)&chopstick[i]);
	}
	for(i=0; i<N; i++) {
		pthread_join(thread_id[i], NULL);
	}

	return 0;

}


