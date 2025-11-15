#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) //do not use this command line argument yet, it is for later stage
{
    int e_pid[2],m_pid[2], e_re, m_re;
    int i=1, j=1;
    char *e_otherprogram = "./t2_ear"; 
    char *m_otherprogram = "./t2_mouth"; 
    char *e_args[3]; /* array to hold arguments to pass to exec system call */
    char *m_args[3]; // array to hold arguments to pass to exec system call 
    char eb_buffer, mb_buffer;

    e_args[0]= e_otherprogram;
    e_args[1]= NULL;
    //e_args[2]= NULL; //it is for later stage

    m_args[0]= m_otherprogram;
    m_args[1]= NULL;
    //m_args[2]= NULL; //it is for later stage
   
    e_pid[i] = fork();
    if(e_pid[i]>=0)
    {
        if(e_pid[i] == 0)
        {
	   // printf("%d\t %d\n",getpid(), getppid());
            e_re = execv(e_otherprogram, (char **) e_args);
            if(e_re == -1)
            {
                printf("Error in running %s \n",e_otherprogram);
                perror("see the errno\n");
                return 0;
            }
            return 0;
        }
	else if(e_pid>0){
	//data processing function
	//write output in file
        //fprintf(fp, "%s\n", buffer); //this buffer needs to be large enough to store the processed data
        //fflush(fp); // ensures data is written immediately
	//fseek(fp,0,SEEK_SET);

	//fclose(fp);
    	//-------calling mouth------
      	m_pid[j] = fork();
    		if(m_pid[j]>=0)
    		{
        		if(m_pid[j] == 0)
        		{
    				//while(1){ //it is for later stage
				//fread(mb_buffer,1,1,fp);
    					//if(buffer == '1'){ //if it is one, mouth can read & speak; if it is 0, brain is writing, wait;
            					m_re = execv(m_otherprogram, (char **) m_args);
            					if(m_re == -1)
            					{
                					printf("Error in running %s \n",m_otherprogram);
                					perror("see the errno\n");
                					return 0;
            					}
            					return 0;
        				//}
				//}
    			}else{
				wait(NULL);
			}
		}
    		else
    		{
        		printf("Error calling fork() \n");
        		perror("see the errno\n");
        		return 0;
    		}

		printf("parent process executing");
		wait(NULL);
	}
    }

    else
    {
        printf("Error calling fork() \n");
        perror("see the errno\n");
        return 0;
    }
    
}
