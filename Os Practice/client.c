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
	printf("Client starting:");
	int len;
	int msgid = msgget(7891, 0777);
	struct Message m;
	m.type = 1;
	while(msgrcv(msgid,&m,sizeof(m.msg),1,0) != -1)
	{
		printf(" From Server : %s",m.msg);
		fgets(m.msg,sizeof(m.msg),stdin) ;
	 	len = strlen(m.msg);
	 	if(m.msg[len-1] == '\n'){
	 	 	m.msg[len-1] = '\0';
	 	}
	 	msgsnd(msgid,&m,sizeof(m.msg),0);
	}
	return 0;
}
