// C3_4.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>

#pragma warning(disable:4996)

void BubSort(int *x, int length) {
	int temp;
	int i, j;
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
	FILE *fp = fopen("Lesson04.txt", "r"); //ファイルの読み込み宣言
	if (fp == NULL) { //失敗したときの例外処理
		printf("Can't create file.\n");
		return -1;
	}
	char str[300]; //文字列を格納する箱（余裕のある大きさで）
	fgets(str, sizeof(str), fp); //ファイルの文字列を読み込み、箱に入れる
	//puts(str); //デバック用
	fclose(fp); //ファイルの読み込み終了宣言

	int score[100]; //箱の用意
	int sum = 0, num = 0, A = 0, B = 0, C = 0,
		D = 0, F = 0; //箱の用意
	char *tp;
	tp = strtok(str, "\t"); //一回目の分割
	while (tp != NULL) {
		score[num] = atoi(tp); //変換
		sum += score[num]; //合計値

		if (score[num] >= 90) A++; //判定
		else if (score[num] >= 80) B++;
		else if (score[num] >= 70) C++;
		else if (score[num] >= 60) D++;
		else F++;
		//printf("A:%d, B:%d, C:%d, D:%d,F:%d?n", A,B,C,D,F);
		num++; //点数の個数
		tp = strtok(NULL, "\t");
		//二回目以降の分割

	}
	BubSort(score, num);
	FILE *fp2 = fopen("test.txt", "w"); //出力ファイルを作成
	if (fp2 == NULL) { //例外処理
		printf("Can't create file.\n");
		return -1;
	}
	fprintf(fp2, "A:%d, B:%d, C:%d, D:%d, F:%d\n", A, B, C, D, F);
	fprintf(fp2, "average score:%lf\n", (double)sum / (double)num);
	fprintf(fp2, "median:%d\n", score[(num + 1) / 2]);
	fclose(fp2); //閉じる

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
