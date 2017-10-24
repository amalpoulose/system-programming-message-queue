/*2.WAP to delete all message queues?*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main(void)
{
int id,key;
system("ipcs -q");
printf("enter the message queue key : ");
scanf("%d",&key);
id=msgget(key,0);
if(id<0)
  printf("\n\nMessage queue not exist\n");
msgctl(id,IPC_RMID,0);
printf("\n  Done\n");
return 0;
}
