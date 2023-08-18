#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void sort(int arr[] ,int size){
 	int k,j,i;
 	for (i = 1; i < size; i += 1)
 	{
 		k = arr[i];
 		j = i-1;
 		while (j>=0 && arr[j]>k)
 		{
 			arr[j+1] = arr[j];
 			j--;
 		}
 		arr[j+1] = k;
 	}
}
int main (int argc, char *argv[])
{
	int request[] = {86,470,91,17,94,150,102,130};
	int *frequest = malloc(sizeof(int)*11);
	int i;
	for (i = 0; i < 8; i += 1)
	{
		frequest[i] = request[i];
	}
	frequest[i] = 0;i++;
	frequest[i] = 143;i++; // current 
	frequest[i] = 499;	// end
	int direction = 1;
	sort(frequest,11);
	int curr = 0;
	for (int i = 0; i < 11; i += 1)
	{
		if(frequest[i] == 143){
		 	curr = i;
		 	printf("Current = %d ",curr);
		}
	}
	int head = 0;
	if(direction > 0){
		int track = 0;
	 	bool rend = true;
	 	bool lend = true;
	 	while(rend){
	 	 	if(curr < 9){
	 	 	printf("\n");
	 	 	 	track++;
	 	 	 	curr++;
	 	 	 	head = head + frequest[curr] - frequest[curr-1];
	 	 	 	for(int x=0;x<curr;x++){
	 	 	 	 	printf("\t");
	 	 	 	}
	 	 	 	printf("*");
	 	 	}else{
	 	 	 	rend = false;
	 	 	}
	 	}
	 	while(lend){
	 	 	if(curr > 1){
	 	 	printf("\n");
	 	 	 	track--;
	 	 	 	curr--;
	 	 	 	head = head + frequest[curr+1] - frequest[curr];
	 	 	 	for(int x=0;x<curr;x++){
	 	 	 	 	printf("\t");
	 	 	 	}
	 	 	 	if(track<0){
	 	 	 	 	printf("*");
	 	 	 	}
	 	 	}else{
	 	 	 	lend = false;
	 	 	}
	 	}
	}
	printf("Head movements = %d",head);
	return 0;
}
