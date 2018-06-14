/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "headerMsg.h"
#include "dataAcces.c"
#include <sys/time.h>


#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10     // how many pending connections queue will hold

#define BUFFERSIZE 1024  // Bytes 

struct sockaddr* cliaddr;
socklen_t clilen;
double time_diff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;
     
    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
     
    diff = (double)y_ms - (double)x_ms;
     
    return diff;
}

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
// Resp point to the response string created in request
char* receiveMsg(int sockt){
	struct headerMsg hMsg;
	char buf[BUFFERSIZE];
	int numbytes;
	char *resp;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t addr_len;

        
    addr_len = sizeof their_addr;

	numbytes = recvfrom(sockt, buf, BUFFERSIZE-1, 0, cliaddr, &clilen);
	if (numbytes  == -1) {
        perror("recv");
        exit(1);
    }
	if(numbytes > 0){
		// printf("received = %s\n", buf);

		memcpy(&hMsg, buf, sizeof(struct headerMsg));

		// printf("Function name = %d\n", hMsg.functionName);
		// printf("Payload Size = %d\n", hMsg.sizePayload);
		// printf("Discipline = %s\n", hMsg.disciplineId);
		// printf("Payload = %s\n", hMsg.disciplineId);
		resp = getRequest(hMsg);
		return resp;
	}
   
}

//Function to write and send a msg 
void writeMsg(int sockt, char* resp){
	int numbytes;
	if(strlen(resp) > BUFFERSIZE){
		
	}
    numbytes = sendto(sockt, resp, BUFFERSIZE, 0, cliaddr, clilen);
    if ( numbytes == -1)
        perror("send");
}
void executeRequests(int sockt){
	double timesVetor[30];
	struct timeval before, after;
	char* resp;
   
	for(int i=0; i<30; i++){
        resp = receiveMsg(sockt);
        gettimeofday(&before, NULL);
        writeMsg(sockt, resp);	
        gettimeofday(&after, NULL);
        timesVetor[i]= time_diff(before , after) ; 
     }
     for(int i=0; i<30; i++){
		printf(" %.0lf  \n" , timesVetor[i]);
	}
}

int main(void)
{
    int sockfd;  // listen on sock_fd, new connection on socket
    struct addrinfo hints, *servinfo, *p;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    // struct headerMsg hMsg;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

             if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

   

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    memset(&cliaddr, 0, sizeof cliaddr);
    cliaddr = p->ai_addr;
    clilen = p->ai_addrlen;

    freeaddrinfo(servinfo);  // all done with this structure
       

    printf("server: waiting to recive Datagram ...\n");
 
    
    executeRequests(sockfd); 

    close(sockfd); // child doesn't need the listener

    return 0;
}
