#include<stdio.h> //need it for fprintf
#include<unistd.h> //need it for fork()
//#include<sys/types.h> don't know its use 
#include<sys/stat.h> //need it for umask
#include<signal.h> //need it for SIGTERM AND SIGINT
#include<stdlib.h> //need it for exit(0)

int keep_running = 1;

//function to gracefully handle the exiting 
void handle_signals(int sig){
	if(sig==SIGTERM || sig==SIGINT){
		keep_running = 0;
	}
}


int main(){
	pid_t pid1;
	pid1 = fork();

	if(pid1<0) exit (1);
	if(pid1>0) exit (0);//kill the parent process
	
	setsid();
	chdir("/");
	umask(027);

	signal(SIGTERM, handle_signals);
	signal(SIGINT, handle_signals);
		
	int i=0;
	while(keep_running){
		FILE *fp;
	       	fp = fopen("/tmp/daemon.log", "a+");
		
		if(fp){
			fprintf(fp, "My Daemon is running of pid:%d for %d times\n", getpid(),i);
			i++;
			fclose(fp);
		}

		sleep(5);
	}

		FILE *fp;
	       	fp = fopen("/tmp/daemon.log", "a+");

		if(fp){
			fprintf(fp, "Daemon is shutting down, byeeeee");
			fclose(fp);
		}

	return 0;
}
