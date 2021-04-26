#include <stdio.h>
#include <ctype.h>

int main(){
	int sumScore = 0;
	while(1){
		int i = 0;
		printf("0か1を合計5つ入力してください。\n");
		char input[20];
		scanf("%s", input);
		
		int includeChar = 0;
		for(i = 0; i < 20; i++){
			if(input[i] == '\0'){
				break;
			}
			if(isdigit(input[i])){
			//文字でない
			}else{
			//文字発見
				includeChar = 1;
			}
		}
		if(includeChar == 1){
			printf("文字が含まれています。\nゲームを終了します。\n");
			break;
		}
		
		int includeMoreThan1 = 0;
		i = 0;
		while(input[i] != '\0'){
			char s[2];
			s[0] = input[i];
			s[1] = '\0';//文字列の終端文字(必須)
			int num = atoi(s);
			if(num > 1 || num < 0){
				includeMoreThan1 = 1;
			}
			i++;
		}
		if(includeMoreThan1 == 1){
			printf("入力エラー。\n0、1以外の数字が含まれています。\n");
			continue;//whileの最初に戻る
		}

		char answer[6];
		answer[5] = '\0';

		for(i = 0; i < 5; i++){
			int j = rand() % 2;

			if(j == 0){
				answer[i] = '0';
			}
			if(j == 1){
				answer[i] = '1';
			}
		}
		int k = rand() % 5;
		answer[k] = '0';

		int try1 = 0;
		for(i = 0; i < 5; i++){
			if(input[i] == '1'){
				try1++;
			}
		}
		
		int addScore = 0;
		if(try1 == 1){
			addScore = 50;
		}else if(try1 == 2){
			addScore = 40;
		}else if(try1 == 3){
			addScore = 30;
		}else if(try1 == 4){
			addScore = 20;
		}else if(try1 == 5){
			addScore = 10;
		}else if(try1 == 0){
			addScore = 10;
		}
		int score = 0;
		for(i = 0; i < 5; i++){
			if(input[i] == '1'){
				if(input[i] == answer[i]){
					score += addScore;
				}
				if(input[i] != answer[i]){
					score -= 10;
				}
			}
		}
		
		if(addScore == 0) {
			score += 10;
		}
		
		printf("%d点獲得しました！\n", score);
		sumScore += score;
		printf("現在の合計得点は%dです。\n",sumScore);
	}
}
