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

int main(void)
{

	int id,size=0,count=0,arr[2];
	struct msg1 v1;
	id=msgget(5,IPC_CREAT|0664);
	perror("msgget");
	msgrcv(id,&v1,sizeof(v1),2,0);
	printf("Path = %s\n",v1.s);
	DIR *dp;
	char s[500];
	dp=opendir(v1.s);
	perror("opendir");
	struct dirent *v;
	struct stat p;
	while(v=readdir(dp))
	{
		if(v->d_name[0]=='.')
			continue;
		strcpy(s,v1.s);
		strcat(s,"/");
		strcat(s,v->d_name);
		printf("  %-10s",v->d_name);
		stat(s,&p);
		printf("  %-5d ",(int)p.st_size);
		size+=p.st_size;
		count+=p.st_nlink;
		printf("  %d  \n",(int)p.st_nlink);
	}

	struct msg2 v2;
	v2.mtype=3;
	v2.arr[0]=size;
	v2.arr[1]=count;
	msgsnd(id,&v2,sizeof(arr),0);

	printf("\n  Done\n");
	return 0;
}


