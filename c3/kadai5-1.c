// C3_2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include "string.h"

#pragma warning(disable:4996)

struct Data {
	char Name[30];
	char Country[30];
	double Short;
	double Free;
};

void BubSort(double *x, int length) {
	int temp;
	int i = 0;
	int j = 0;
	for (i = 0; i < length - 1; i++) {
		for (j = 0; j < length - 1 - i; j++) {
			if (x[j] > x[j + 1]) { // 前の要素の方が大きいならば
				temp = x[j]; // 交換する
				x[j] = x[j + 1];
				x[j + 1] = temp;
			}
		}
	}
}

int main()
{
	struct Data score[100];
	FILE *fp = fopen("Lesson05.txt", "r");
	if (fp == NULL) {
		printf("Can't read file. \n");
		return -1;
	}

	int i = 0;
	char str[100];
	char *tmp;
	while ((fgets(str, sizeof(str), fp)) != NULL) {
		char *p = strchr(str, (int)'\n');
		if (p != NULL) *p = '\0';
		tmp = strtok(str, ",");
		strcpy(score[i].Name, tmp);
		tmp = strtok(NULL, ",");
		strcpy(score[i].Country, tmp);
		tmp = strtok(NULL, ",");
		score[i].Short = atof(tmp);
		tmp = strtok(NULL, ",");
		score[i].Free = atof(tmp);
		i++;
	}
	fclose(fp);

	double S[100];
	double F[100];
	double SSum = 0;
	double FSum = 0;
	int j = 0;
	for (j = 1; j < i; j++) {
		S[j] = score[j].Short;
		F[j] = score[j].Free;

		SSum += score[j].Short;
		FSum += score[j].Free;
	}

	BubSort(S, i - 1);
	BubSort(F, i - 1);

	printf("Short平均値 = %lf\n", SSum / (i - 1));
	printf("Free平均値 = %lf\n", FSum / (i - 1));
	printf("Short中央値 = %lf\n", S[i / 2]);
	printf("Free中央値 = %lf\n", F[i / 2]);

	return 0;

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
