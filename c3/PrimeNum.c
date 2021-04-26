#include<stdio.h>

int main(){
	int i;
	for(i = 1; i <= 100; i++){
		int cnt = 0;
		int j;
		for(j = i;j >= 1; j--){
			if(i % j == 0){
				cnt++;
			}
		}
		if(cnt == 2){
			printf("%d\n", i);
		}
	} 
	return 0;
}
