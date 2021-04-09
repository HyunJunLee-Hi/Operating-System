#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>

#define COUNTING_NUMBER 2000000
//shared memory
struct smstruct{
	int processidassign;
	int turn;
	int flag[2];
	int critical_section_variable;
}*s;

//peterson
void lock(struct smstruct *s, int self) {
	s->flag[self] = 1;
	s->turn = 1-self;
	while(s->flag[1-self] == 1 && s->turn == 1 - self);
}

void unlock(struct smstruct *s, int self) {
	s->flag[self] = 0;
}



int main() {
	
	int localcount = 0;
	int Myorder, i;
	int shmid;
	void *shmaddr;
	int ret;
	//get shared memory id
	shmid = shmget((key_t)1234, 1024, IPC_CREAT|0666);
	if(shmid == -1) {
		perror("shared memory access is failed\n");
		return 0;
	}
	//attach the shared memory
	shmaddr = shmat(shmid, (void *)0, 0);
	if(shmaddr == (char *)-1) {
		perror("attach failed\n");
		return 0;
	}

	s = (struct smstruct *)shmaddr;
	Myorder = s-> processidassign++;	
	printf("Myorder = %d, process pid = %d\n", Myorder, getpid());
	//peterson
	for(i = 0; i<COUNTING_NUMBER; i++) {
		localcount++;
		lock(s, Myorder);
		s->critical_section_variable++;
		unlock(s, Myorder);
	}

	printf(" child finish! local count = %d\n", localcount);
	//detach the shared memory
	ret = shmdt(shmaddr);
	if(ret == -1) {
		perror("detach failed");
		return 0;
	}
	//remove
	ret = shmctl(shmid, IPC_RMID, 0);
	if(ret == -1) {
		perror("remove failed");
		return 0;
	}
	
	return 0;
}
