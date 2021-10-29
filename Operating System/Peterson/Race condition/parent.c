#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>
//shared memory
struct smstruct{
	int processidassign;
	int turn;
	int flag[2];
	int critical_section_variable;
} *s;

int main() {
	pid_t pid1, pid2;
	int status1, status2;
	int shmid;
	int i;
	void *shmaddr;
	//get shared memory id
	shmid = shmget((key_t)1234, 1024, IPC_CREAT|0666);
	if(shmid < 0) {
		perror("shmget");
		return 0;
	}
	//attach the shared memory
	shmaddr = shmat(shmid, (void *)0, 0);
	if(shmaddr == (char *)-1) {
		perror("failed attach address\n");
		return 0;
	}

	s = (struct smStruct *)shmaddr;
	s -> turn = 0;
	s -> processidassign = 0;
	s -> flag[0] = 0;
	s -> flag[1] = 0;
	s -> critical_section_variable = 0;
	//child process fork
	pid1 = fork();
	if(pid1 == 0) {
		execl("./child", NULL);
	}
	else {
	
		pid2 = fork();
		if(pid2 == 0) {
			execl("./child", NULL);
		}
	}

	//wait child process exit
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);

	printf("Actual Count: %d | Expected Count: 4000000\n", s->critical_section_variable);
	
	//detach the shared memory
	if(shmdt(shmaddr)==-1) {
		perror("detach failed\n");
		return 0;
	}

	return 0;

}
