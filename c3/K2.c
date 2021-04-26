// K2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>

#pragma warning(disable:4996)

int main()
{
	int totalscore = 0;
	while (1) {

		char input[10];

		printf("1か0を計5つ入力してください。\n");
		scanf("%s", input);

		int i = 0;
		int exit = 0;

		while (input[i] != '\0') {
			if (isdigit(input[i]) ) {
			}
			else {
				exit = 1;
			}
			i++;
		}

		if (exit == 1) {
			printf("終了します");
			break;
		}

		i = 0;
		char tmp[2];
		int hairetsu[10];
		int exNum = 0;
		while (input[i] != '\0') {
			tmp[0] = input[i];
			tmp[1] = '\0';
			hairetsu[i] = atoi(tmp);
			if (1 < hairetsu[i] || hairetsu[i] < 0) {
				exNum = 1;
			}
			i++;
		}

		if (exNum == 1) {
			continue;
		}
		
		char answer[6];
		answer[5] = '\0';

		for (i = 0; i < 5; i++) {
			int j = rand() % 2;

			if (j == 0) {
				answer[i] = '0';
			}
			if (j == 1) {
				answer[i] = '1';
			}
		}
		int k = rand() % 5;
		answer[k] = '0';

	//	printf("答え = %d%d%d%d%d\n", ans[0], ans[1], ans[2], ans[3], ans[4]);

		int add = 0;
		int No1 = 0;
		int score = 0;
		for (i = 0; i < 5; i++) {
			if (hairetsu[i] == 1) {
				No1++;
			}
		}

		if (No1 == 0) {
			score += 10;
		}
		else if (No1 == 1) {
			add = 50;
		}
		else if(No1 == 2){
			add = 40;
		}
		else if (No1 == 3) {
			add = 30;
		}
		else if (No1 == 4) {
			add = 20;
		}
		else {
			add = 10;
		}

		for (i = 0; i < 5; i++) {
			if (hairetsu[i] == 1 && answer[i] == '1') {
				score += add;
			}
			else if (hairetsu[i] == 1 && answer[i] == '0') {
				score -= 10;
			}
		}


		

		printf("%d点獲得\n", score);
		totalscore += score;
		printf("総計スコア = %d点\n", totalscore);




	}


}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
