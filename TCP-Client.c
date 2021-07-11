#include<unistd.h>
#include<sys/select.h>
#include<stdio.h>
#include<poll.h>
#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#define MAX 80
#define N 20
#define SA struct sockaddr
void func(int sockfd)
{
float highest;
char buff[MAX];
int arr[N];
int n,i;
int ans[10];
struct timespec begin, end;
float time[4];


//Timeout settings using poll system call
  int timeout=7000,retpoll;
  struct pollfd fds[1];
  fds[0].fd=0;
  fds[0].events=POLLIN;
printf("\n\nYour time starts in 5 seconds....\n");
sleep(5);

clock_gettime(CLOCK_MONOTONIC_RAW, &begin);

printf("Random array is : \n[");
recv(sockfd,&arr,sizeof(arr),0);
for(i=0;i<N;i++)
{
printf("%d  ",arr[i]);
if(i%5==0 && i!=0)
printf("  \n");
}
printf("\b]\n");
bzero(buff,sizeof(buff));
printf("\nCount of negative numbers?\n");
retpoll=poll(fds,1,timeout);
if(retpoll==0){
printf("Time out: Sorry\n\n");
return 0;
}

 if(fds[0].revents){
scanf("%d",&ans[0]);
printf("\nMax no?\n");
}

retpoll=poll(fds,1,timeout);
if(retpoll==0){
printf("Time out: Sorry\n\n");
return 0;
}

 if(fds[0].revents){
scanf("%d",&ans[1]);
printf("\nMin no?\n");
}

retpoll=poll(fds,1,timeout);

if(retpoll==0){
printf("Time out: Sorry\n\n");
return 0;
}


if(fds[0].revents){
scanf("%d",&ans[2]);
printf("\nCount of Positive Numbers?\n");
}

retpoll=poll(fds,1,timeout);

if(retpoll==0){
printf("Time out: Sorry\n\n");
return 0;
}


if(fds[0].revents){
scanf("%d",&ans[3]);
}


clock_gettime(CLOCK_MONOTONIC_RAW, &end);
time[0]=(end.tv_nsec - begin.tv_nsec) / 1000000000.0 + (end.tv_sec  - begin.tv_sec);
printf("\nTotal time you took: %f seconds\n", time[0]);
send(sockfd,&ans,sizeof(ans),0);
send(sockfd,&time[0],sizeof(time[0]),0);
read(sockfd,buff,sizeof(buff));
printf("\nMessage from Server : %s\n\n",buff);
}

int main(int argc, char*argv[])
{
int u;
printf("\n-----------------<WELCOME TO FIND-ME-FAST>-------\n\n");
printf("Instructions:\t1.You will be showed 20 random integers in the range of -20 to 20.\n\t\t2.You Need to answer count of negative numbers, maximum number, minimum number\n\t\tand count of positive numbers\n\t");
printf("\t3.Time Limit for each question is 7 seconds.\n");
do
{
printf("Hit 1 to continue...\n");
scanf("%d",&u);
}
while(u!=1);
int sockfd,connfd;
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
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(atoi(argv[1]));
if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))!=0)
{
printf("[-]Connection with the server failed...\n");
exit(0);
}
else
printf("[+]Connected to the server..\n");
func(sockfd);
close(sockfd);
}






