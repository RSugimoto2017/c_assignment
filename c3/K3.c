// K3.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>

#pragma warning(disable:4996)

int main()
{
	int Total = 0;
	while (1) {
		char str[40];
		scanf("%s", str);
		if (str[5] != '\0') {
			printf("文字数が違います\n");
			continue;
		}
		int i;
		int includeNum = 0;
		for (i = 0; i < 5; i++) {
			if (isdigit(str[i])) {
				includeNum = 1;
			}
		}
		if (includeNum == 1) {
			printf("Bye\n");
			break;
		}

		int exChar = 0;
		i = 0;
		while(str[i] != '\0'){
			if (str[i] != 'a' && str[i] != 'b') {
				exChar = 1;
			}
			i++;
		}
		if (exChar == 1) {
			printf("aかbでない文字があります\n");
			continue;
		}

		char ans[6];
		int k;
		int l;

		for (i = 0; i < 5; i++) {
			k = rand() % 2;
			if (k == 0) {
				ans[i] = 'a';
			}
			else {
				ans[i] = 'b';
			}
		}
		
		k = rand() % 5;
		l = rand() % 5;
		while (l == k) {
			l = rand() % 5;
		}

		ans[k] = 'a';
		ans[l] = 'b';
		ans[5] = '\0';

		printf("答え = %s\n", ans);

		int aflag = 0;
		int bflag = 0;
		int Score = 0;

		for (i = 0; i < 5; i++) {
			if (str[i] == 'a' && str[i] == ans[i] && bflag == 0) {
				Score += 10;
				aflag = 1;
			}
			else if (str[i] == 'b' && str[i] == ans[i] && aflag == 0) {
				Score += 10;
				bflag = 1;
			}
			else if (str[i] == 'a' && str[i] == ans[i] && bflag == 1) {
				Score += 60;
				aflag = 0;
				bflag = 0;
			}
			else if (str[i] == 'b' && str[i] == ans[i] && aflag == 1) {
				Score += 60;
				aflag = 0;
				bflag = 0;
			}
		}

		printf("%d点獲得！\n", Score);
		Total += Score;
		printf("合計%d点\n", Total);



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
