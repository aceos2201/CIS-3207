#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void* doSomeThing(void *arg){

    
 }

int main(int argc, char *argv[])
{

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];


    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

// if(fork() == 0)
//      {sleep(1);}
//  else if(fork() == 0){sleep(1);}
//  else if(fork() == 0){sleep(1);}
    
    // srand(time(NULL));
    // randomnumber = rand();
    // fp = fopen("dictonary.txt", "r");
    // bzero(randwordbuff, 256);
    // while(fgets(randwordbuff, 256, fp) && randomnumber > 0)
    // {
    //                 randomnumber--;
    // }

while(1){
    //portno = atoi(argv[2]);
    portno = 51717;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,256,stdin);
    wait(2);
    n = write(sockfd,buffer,strlen(buffer));
    //n = write(sockfd,"Hello", 256);
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,256);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);

    close(sockfd);

    sleep(1);
    }
    return 0;
}