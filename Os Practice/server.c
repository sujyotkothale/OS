#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/ipc.h>

struct Message{
	long int type;
	char msg[256];
};

int main (int argc, char *argv[])
{
	printf("Server starting:");
	int len;
	int msgid = msgget(7891,IPC_CREAT | 0777);
	struct Message m;
	m.type = 1;
	while(fgets(m.msg,sizeof(m.msg),stdin) != NULL)
	{
	 	len = strlen(m.msg);
	 	if(m.msg[len-1] == '\n'){
	 	 	m.msg[len-1] = '\0';
	 	}
	 	msgsnd(msgid,&m,len+1,0);
	 	msgrcv(msgid,&m,sizeof(m.msg),1,0);
	 	printf(" From Client : %s",m.msg);
	}
	msgctl(msgid,IPC_RMID,0);
	return 0;
}
