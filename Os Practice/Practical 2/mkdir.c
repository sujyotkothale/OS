#include<stdio.h>
#include<stdlib.h>
int main (int argc, char *argv[])
{
	int check = mkdir("hello",0777);
	printf("%d",check);
	return 0;
}
