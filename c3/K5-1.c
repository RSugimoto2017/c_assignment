// K5-1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#pragma warning(disable:4996)

struct Record{
	char Name[40];
	char Country[40];
	double Short;
	double Free;
};

void BubSort(double *x, int length) {
	int i, j;
	double tmp;
	for (i = 0; i < length - 1; i++) {
		for (j = 0; j < length - 1; j++) {
			if (x[j] > x[j + 1]) {
				tmp = x[j];
				x[j] = x[j + 1];
				x[j + 1] = tmp;
			}
		}
	}
}

int main()
{
	struct Record Score[40];
	FILE *fp = fopen("Lesson05.txt", "r");
	char str[100];
	char *tmp;
	int NoP = 0;
	while(fgets(str, sizeof(str), fp) != NULL){
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
		NoP++;
	}
	fclose(fp);

	int i;
	double ShortSum = 0;
	double FreeSum = 0;
	double Shortqueue[40];
	double Freequeue[40];

	for (i = 1; i < NoP; i++) {
		ShortSum += Score[i].Short;
		FreeSum += Score[i].Free;
		Shortqueue[i - 1] = Score[i].Short;
		Freequeue[i - 1] = Score[i].Free;
	}

	BubSort(Shortqueue, NoP);
	BubSort(Freequeue, NoP);

	printf("Short平均 = %lf\n", ShortSum / (NoP-1));
	printf("Free平均 = %lf\n", FreeSum / (NoP-1));
	printf("Short中央 = %lf\n", Shortqueue[(NoP+1)/2]);
	printf("Free中央 = %lf\n", Freequeue[(NoP + 1) / 2]);

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
