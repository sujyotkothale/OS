#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
int main (int argc, char *argv[])
{
	int fd = open("demo.txt",O_RDWR,0777);
	char buff[200];
	read(fd,buff,sizeof(buff));
	char buf2[] = "hello world";
	if(strstr(buff,buf2) != 0){
	 	printf("Match found");
	}
	close(fd);
	return 0;
}
