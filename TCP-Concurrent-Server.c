#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#define MAX 80
#define N 20
#define PORT 8870
#define SA struct sockaddr


void func(int sockfd)
{
float highest;
char buff[MAX];
float clitime[20];
int ne=0;
int arr[20],i,num,max,min,po=0,n,ans[10];

//Random Array Generation
    srand(time (NULL));
    for(i=0; i<20; i++)
    {
    num=(rand()%50 -30);
    arr[i]=num;
    }
max=arr[0];
min=arr[0];

//Finding Max No., Min No. and count of negatives and positives
for(i=0; i<20; i++)
{
if(arr[i]>max)
max=arr[i];
if(arr[i]<min)
min=arr[i];
if(arr[i]<0)
ne++;
if(arr[i]>0)
po++;
}
printf("Neg=%d\n",ne);
printf("Max=%d\n",max);
printf("Min=%d\n",min);
printf("Po=%d\n",po);
send(sockfd,&arr,sizeof(arr),0);
bzero(buff,MAX);

//Recieving Answer from client response time and checking

recv(sockfd,&ans,sizeof(ans),0);
recv(sockfd,&highest,sizeof(highest),0);
printf("Time Taken by client: %f\n",highest);
if(ans[0]==ne && ans[1]==max && ans[2]==min&& ans[3]==po)
write(sockfd,"Congrats! All answers are correct!",34);
else
write(sockfd,"Uh-oh! Better luck next time!",30);
exit(0);
}

int main(int argc, char *argv[])
{
pid_t childpid;
int sockfd,connfd,len;
struct sockaddr_in servaddr,cli;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==-1)
{
printf("[-]Socket creation failed...\n");
exit(0);
}
else
printf("[+]Socket successfully created...\n");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(atoi(argv[1]));
if((bind(sockfd,(SA*)&servaddr, sizeof(servaddr)))!=0)
{
printf("[-]Socket bind failed...\n");
exit(0);
}
else
printf("[+]Socket successfully binded...\n");
if((listen(sockfd,5))!=0)
{
printf("[-]Listen failed...\n");
exit(0);
}
else
printf("[+]Server listening..\n");
len=sizeof(cli);
while(1)
{
connfd=accept(sockfd,(SA *)&cli,&len);
if(connfd<0)
{
printf("[-]Server acccept failed...\n");
}
else
printf("[+]Connection accepted from %s: %d:\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));

//Fork system call to handle new clients using child process.
childpid=fork();
if((childpid==0))
{
close(sockfd);
while(1)
{
func(connfd);
}
}
}
close(connfd);
}



