// C3_1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include "string.h" 

int main()
{
	char input[100];
	int smallcnt = 0;
	int wordcnt = 0;

	scanf("%[^\n]%*s", input);
	int i = 0;
	while (input[i] != '\0') {
		//printf("%c", input[i]);
		if ('a' <= input[i] && input[i] <= 'z') {
			smallcnt++;
			
		}
		i++;
	}

	char* tmp;

	tmp = strtok(input, " ");
	while (tmp != NULL) {
		wordcnt++;
		tmp = strtok(NULL, " ");
	}

	printf("smallletter = %d\n", smallcnt);
	printf("word = %d", wordcnt);
	

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
