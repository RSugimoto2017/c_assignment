#include <stdio.h>
#include <ctype.h>

int main(){
	int sumScore = 0;
	while(1){
		int i = 0;
		printf("aかbを合計5つ入力してください。\n");
		char input[20];
		scanf("%s",input);
		
		int includeDigit = 0;
		for(i = 0;i < 20; i++){
			
			if(input[i] == '\0'){
				break;
			}
			
			if(isdigit(input[i])){
				includeDigit = 1;
			}else{
			
			}
		}
		if(includeDigit == 1){
			printf("数字が含まれているため、ゲームを終了します。\n");
			break;
		}
		
		int includeExceptAB = 0;
		i = 0;
		while(input[i] != '\0'){
			/*char s[2];
			s[0] = input[i];
			s[1] = '\0';*/
			if(input[i] != 'a' && input[i] != 'b'){
				includeExceptAB = 1;
			}
			i++;
		}
		if(includeExceptAB == 1){
			printf("入力エラーです。\na、b以外の文字が含まれています。\n");
			continue;
		}

		char answer[6];
		answer[5] = '\0';

		for(i = 0; i < 5; i++){
			int j = rand()%2;
			
			if(j == 0){
				answer[i] = 'a';
			}
			if(j == 1){
				answer[i] = 'b';
			}
		}

		printf("正解 = %s\n",answer);
		
		int correctA = 0;
		int correctB = 0;
		
		int score = 0;
		for(i = 0; i < 5; i++){
			if(input[i] == 'a'){
				if(input[i] == answer[i]){
					score += 10;
					correctA = 1;
				}
			}
			if(input[i] == 'b'){
				if(input[i] == answer[i]){
					score += 10;
					correctB = 1;
				}
			}
			if(correctA == 1 && correctB == 1){
				score += 50;
				correctA = 0;
				correctB = 0;
			}
		}

		printf("%d点獲得しました！\n", score);
		sumScore += score;
		printf("現在の合計得点は%d点です。\n", sumScore);
		
		
	};
}
