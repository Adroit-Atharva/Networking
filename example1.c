#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){

	int pid1;
	int status;
	pid1 = fork();

	if(pid1==0){
		printf("Child\n");
		printf("%d\n", pid1);
		
		char *args[] = {"ls", "-l", NULL};
        	execv("/bin/ls", args); // Replace with `ls`
        	perror("execv failed"); // Only runs if execv fails
		printf("Hello fucker\n");//everything written after execv inside child process is skipped since it creates an entierly new program
					 //instead of the existing one while retaining the original PID.
	}else if(pid1>0){
		printf("Parent\n");
		printf("%d\n", pid1);
		wait(&status);
		printf("child is finished\n");
	}else{
		printf("error:\n");
	}

	return 0;
}
