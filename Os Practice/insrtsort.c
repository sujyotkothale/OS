#include<stdio.h>
#include<stdlib.h>
void inerstionsort(int arr[],int size){
	int key,j;
 	for (int i = 1;i < size;i += 1)
 	{
 		key = arr[i];
 		j = i-1;
 		while (j>=0 && arr[j] > key)
 		{
 			arr[j+1] = arr[j];
 			j--;
 		}
 		arr[j+1] = key;
 	}
}
int main (int argc, char *argv[])
{
	int arr[] = {3,6,8,1,2,5,1};
	inerstionsort(arr,7);
	int i;
	for (i = 0; i < 7; i += 1)
	{
		printf(" %d ",arr[i]);
	}
	return 0;
}
