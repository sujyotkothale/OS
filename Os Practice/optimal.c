#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main (int argc, char *argv[])
{
	int request[] = {2,3,2,1,5,2,4,5,3,2,5,2};
	int mem[3];
	int index = 0;
	int i;
	int hit = 0;
	for (i = 0; i < 12; i += 1)
	{
		bool found = false;
		for (int j = 0;j < 3;j += 1)
		{
			if(mem[j] == request[i]){
			 	hit = hit + 1;
			 	printf("\n index = %d",i);
			 	found = true;
			 	break;
			}
		}
		if(!found){
		 	bool placed = false;
		 	for (int j = 0;j < 3;j += 1)
			{
				if(mem[j] == 0){
					mem[j] = request[i];
			 		placed = true;
			 		break;
				}
			}
			if(!placed){
			 	bool see[3] = {false,false,false};
			 	int count = 2;
			 	for(int j=i;j<12;j++){
			 	 	for(int x=0;x<3;x++){
			 	 	 	if(request[j] == mem[x] && see[x] == false){
			 	 	 	 	see[x] = true;
			 	 	 	 	count--;
			 	 	 	}
			 	 	}
			 	 	if(count == 0){
			 	 	 	break;
			 	 	}
			 	}
			 	for(int j=0;j<3;j++){
			 	 	if(!see[j]){
			 	 	 	mem[j] = request[i];
			 	 	}
			 	}
			}
		}
	}
	printf(" hits = %d",hit);
	return 0;
}
