// K4.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include <string.h>

#pragma warning(disable:4996)

void BubSort(int *x, int length) {
	int i, j, tmp;
	for (i = 0; i < length - 1; i++) {
		for (j = 0; j < length - 1; j++) {
			if (x[j] < x[j + 1]) {
				tmp = x[j];
				x[j] = x[j + 1];
				x[j + 1] = tmp;
			}
		}
	}
}

int main()
{
	FILE *fp = fopen("Lesson04.txt", "r");

	if (fp == NULL) {
		printf("NG\n");
		return -1;
	}

	char str[1000];
	int Score[1000];
	int NoP = 0;
	char *tmp;
	int A = 0, B = 0, C = 0, D = 0, F = 0;

	while ((fgets(str, sizeof(str), fp)) != NULL) {
		char *p = strchr(str, (int)'\n');
		if (p != NULL) {
			*p = '\0';
		}

		tmp = strtok(str, "\t");
		while (tmp != NULL) {
			Score[NoP] = atoi(tmp);
			if (Score[NoP] >= 90) {
				A++;
			}
			else if (Score[NoP] >= 80) {
				B++;
			}
			else if (Score[NoP] >= 70) {
				C++;
			}
			else if (Score[NoP] >= 60) {
				D++;
			}
			else {
				F++;
			}
			NoP++;
			tmp = strtok(NULL, "\t");
		}

	}
	fclose(fp);

	int sum = 0;
	int i;
	for (i = 0; i < NoP; i++) {
		sum += Score[i];
		//printf("%d\n", sum);
	}

	printf("%d %d %d %d %d\n", A, B, C, D, F);

	printf("平均 = %lf\n", (double)sum / (double)NoP);

		BubSort(Score, NoP);

	printf("中央 = %d\n", Score[NoP / 2]);

	FILE *fp2 = fopen("result.txt", "w");
	if (fp2 == NULL) {
		printf("NG\n");
		return -1;
	}

	fprintf(fp2, "%d %d %d %d %d\n", A, B, C, D, F);
	fprintf(fp2, "平均 = %lf\n", (double)sum / (double)NoP);
	fprintf(fp2, "中央 = %d\n", Score[NoP / 2]);


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
