/*3.Implement full duplex communication using one message queue?
Hint : use different mtypes*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msgbf
{
	long type;
	char s[20];
};

int main(void)
{
	int id;
	struct msgbf v;

	id=msgget(4,IPC_CREAT|0664);
	if(id<0)
	{
		perror("msgget");
		return;
	}
	if(fork())
	{
		while(1)
		{
			v.type=2;
			scanf(" %s",v.s);
			msgsnd(id,&v,strlen(v.s)+1,0);
		} 
	}
	else
	{
		while(1)
		{
			msgrcv(id,&v,sizeof(v),3,0);
			printf("Data : %s\n",v.s);
		}
	}
	return 0;
}
