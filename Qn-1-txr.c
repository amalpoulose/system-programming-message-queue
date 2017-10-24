/* 1.process1 will send directory name to process2.
Process2 after recieving directory name,open directory ,send back sizeof file and no.of hardlinks
to process1. */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/ipc.h>
#include<sys/msg.h>
struct msg1
{
long mtype;
char s[100];
};
struct msg2
{
long mtype;
int arr[2];
};


int main(int argc,char **argv)
{
if(argc!=2)
{
 printf("usage:./outfile path\n");
return;
}
if(opendir(argv[1])==0)
{
perror("opendir");
return;
}
struct msg1 v;
int id;
id=msgget(5,IPC_CREAT|0664);
perror("msgget");
v.mtype=2;
strcpy(v.s,argv[1]);
msgsnd(id,&v,strlen(argv[1])+1,0);
struct msg2 v1;
msgrcv(id,&v1,sizeof(v),3,0);
printf("total size of files in folder : %d\nNumber of hard links : %d\n",v1.arr[0],v1.arr[1]);
return 0;
}
