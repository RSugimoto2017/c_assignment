// K5-2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#pragma warning(disable:4996)

struct Record {
	char Name[30];
	char Country[30];
	double Short;
	double Free;
};

int main(void)
{
	FILE *fp = fopen("Lesson05.txt", "r");
	Record Score[40];

	char str[100];
	int NoP = 0;
	while ((fgets(str, sizeof(str), fp)) != NULL) {
		char *p = strchr(str, (int)'\n');
		if (p != NULL) {
			*p = '\0';
		}
		char *tmp;
		tmp = strtok(str, ",");
		strcpy(Score[NoP].Name, tmp);
		tmp = strtok(NULL, ",");
		strcpy(Score[NoP].Country, tmp);
		tmp = strtok(NULL, ",");
		Score[NoP].Short = atof(tmp);
		tmp = strtok(NULL, ",");
		Score[NoP].Free = atof(tmp);

		NoP++;

	}
	fclose(fp);

	char input[40];
	printf("国名入力");
	scanf("%s%*c", input);

	int i;
	for (i = 1; i < NoP; i++) {
		if (strcmp(Score[i].Country, input) == 0) {
			printf("%s\n", Score[i].Name);
		}
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
