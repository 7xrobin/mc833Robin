/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "headerMsg.h"
#include <sys/time.h>
#include <arpa/inet.h>

#define PORT "3490" /* the port client will be connecting to  */

#define BUFFERSIZE 1024 /* max number of bytes we can get at once */

struct sockaddr* servaddr;
socklen_t servlen;

/* get sockaddr, IPv4 or IPv6: */
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void receiveMsg(int sockt_fd){
	char buf[BUFFERSIZE];
	int numbytes;


	numbytes = recvfrom(sockt_fd, buf, BUFFERSIZE, 0, servaddr, &servlen);

	if(numbytes > 0){
		printf("Cliente Recebeu = %s\n", buf);
	}
	else if (numbytes  == -1) {
        perror("recv");
        exit(1);
    }
    else{
    	printf("Esperando reposta\n");
    	receiveMsg(sockt_fd);
    }

}

//Function to write a msg and send to serve the request, return same of send()
// hMsg passed by value change only inside function
void writeMsg(int sockt_fd, struct headerMsg hMsg){
	int numbytes;
    numbytes = sendto(sockt_fd, (void*)&hMsg, BUFFERSIZE, 0, servaddr, servlen);
    if ( numbytes == -1)
        perror("send");
}

double time_diff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;
     
    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
     
    diff = (double)y_ms - (double)x_ms;
     
    return diff;
}

void executeRequests(int sockfd){
	struct headerMsg hMsg;
	int i, Id;
	char cod[10];
	double timesVetor[30];
	struct timeval before, after;
   
	printf("Digitar tipo de usuário (0 - aluno ; 1 - professor): \n");
	scanf("%d", &hMsg.userType );
    printf("Digitar ID da função: \n");
	scanf("%d", &hMsg.functionName );
	if (hMsg.functionName > 2)
	{
		printf("Digitar Codigo da Disciplina: \n");
		scanf("%s", hMsg.disciplineId);
		if(hMsg.functionName == 6){
			printf("Digitar Comentário para a  Disciplina: \n");
			scanf("%s", hMsg.payload);
		}
		else{
			strcpy(hMsg.payload, "");
		}
	}
	else{
		strcpy(hMsg.disciplineId, "");
	}
    hMsg.sizePayload = strlen(hMsg.payload);
	for(i=0; i<30; i++){
		gettimeofday(&before, NULL);
    	writeMsg(sockfd, hMsg);
    	receiveMsg(sockfd);
      	gettimeofday(&after, NULL);
    	timesVetor[i]= time_diff(before , after) ; 
	}
    printf("Tempos de resposta: \n");
	for(i=0; i<30; i++){
		printf(" %.0lf  \n" , timesVetor[i]);
	}
	
}
int main(int argc, char *argv[])
{
    int sockfd, numbytes;  
    char buf[BUFFERSIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    /* loop through all the results and connect to the first we can */
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    memset(&servaddr, 0, sizeof servaddr);
    servaddr = p->ai_addr;
    servlen = p->ai_addrlen;


    freeaddrinfo(servinfo); /* all done with this structure */
    
    executeRequests(sockfd);
    close(sockfd);

    return 0;
}

