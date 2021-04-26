// K5-3.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include <string.h>

#pragma warning(disable:4996)

struct Record {
	char Name[30];
	char Country[30];
	double Short;
	double Free;
	double Total;
};

void sort(struct Record *a, struct Record *b) {
	char tmp[30];
	int tmp2;
	if (a->Total < b->Total) {
		strcpy(tmp, a->Name);
		tmp2 = a->Total;
		strcpy(a->Name, b->Name);
		a->Total = b->Total;
		strcpy(b->Name, tmp);
		b->Total = tmp2;

	}
}

void BubbleSort(struct Record *a, int length) {
	int i, j;
	for (i = 1; i < length-1; i++) {
		for (j = 1; j < length - 1; j++) {
			sort(&a[j], &a[j + 1]);
		}
	}
}

int main()
{
	struct Record Score[30];
	FILE *fp = fopen("Lesson05.txt", "r");

	char str[100];
	char *tmp;
	char NoP = 0;
	while ((fgets(str, sizeof(str), fp)) != NULL) {
		char *p = strchr(str, (int)'\n');
		if (p != NULL) {
			*p = '\0';
		}
		tmp = strtok(str, ",");
		strcpy(Score[NoP].Name, tmp);
		tmp = strtok(NULL, ",");
		strcpy(Score[NoP].Country, tmp);
		tmp = strtok(NULL, ",");
		Score[NoP].Short = atof(tmp);
		tmp = strtok(NULL, ",");
		Score[NoP].Free = atof(tmp);
		Score[NoP].Total = Score[NoP].Short + Score[NoP].Free;

		NoP++;
		
	}

	int i;

	/*for (i = 1; i < NoP - 1; i++) {
		printf("%s %lf\n", Score[i].Name, Score[i].Total);
	}*/

	BubbleSort(Score, NoP);

	
	for (i = 1; i < NoP - 1; i++) {
		printf("%s %lf\n", Score[i].Name, Score[i].Total);
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
