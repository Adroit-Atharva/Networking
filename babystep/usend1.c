#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include <sys/types.h>
/*

don't understand the header files used below,

stdio is used for basic input and output operations 

stdlib is used for exit() and to deal with dynamic memory 

unistd is used for providing access to POSIX os API and for using the fork() syscall, but we are using it for close()

string is used for string operations such as copy,cmp, concat, but we are using it for memset and strlen

sys/types is not being used in this code cause the program is compiled perfectly and executes perfectly without it 

*/
//#include <sys/socket.h> //i don't know what it is used for cause i literally removed it and the code still worked perfectly without it 
//#include <arpa/inet.h> //don't know why this is used either cause it's not needed 
#include <netinet/in.h> //okay this one is needed for all the sock, net and addr stuff, so i need to see more into it 

#define REMOTEPORT 1234
#define BUFLEN 1024

int main()
{
  int sockfd; //just a var of type int 
  char buffer[BUFLEN]; //just a char[] of size 1024, use is unknown of yet
  char *messageStr = "a very important Good Morning message with 100s of emojis!!!"; //some message
  struct sockaddr_in   receiverAddr;//

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  memset(&receiverAddr, 0, sizeof(receiverAddr));

  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_port = htons(REMOTEPORT);
  receiverAddr.sin_addr.s_addr = INADDR_ANY;

  sendto(sockfd, (const char *)messageStr, strlen(messageStr), 0, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr));

  printf("the very important good morning message sent.....\n");
  close(sockfd);
  return 0;
}

