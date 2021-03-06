// C3-5.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include <string.h>

#pragma warning(disable:4996)

typedef struct Record { //構造体を利用
	char name[30];
	char country[15];
	double short_score;
	double free_score;
	double total_score;
}Record;

void sort(struct Record * a, struct Record *b) {
	//前の数字が大きければ後の数字と交換
	if (a->total_score < b->total_score) {
		char temp[20];
		strcpy(temp, b->name);
		strcpy(b->name, a->name);
		strcpy(a->name, temp);
		char temp2[20];
		strcpy(temp, b->country);
		strcpy(b->country, a->country);
		strcpy(a->country, temp);
		double x = b->total_score;
		b->total_score = a->total_score;
		a->total_score = x;
	}
}

void  BubbleSort(struct Record * x, int length) { //バブルソート
	int i;
	int j;
	for (i = 1; i < length - 1; i++) {
		for (j = 1; j < length - 1; j++) {
			sort(&x[j], &x[j + 1]);
		}
	}
}

int main(void) {
	FILE *fp = fopen("Lesson05.txt ", "r");
	if (fp == NULL) {
		printf("ファイルを開けませんでした。\n");
		return -1;
	}
Record records[30];
int size = 0; //構造体配列の要素数を記憶するための変数
char str[70]; //ファイルから読み込んだ 1 行の文字列 を 一時的 に 記憶する ための箱
double sum1 = 0;
double sum2 = 0;

while (fgets(str, sizeof(str), fp) != NULL) { //読み込めなくなるまで
	char *p = strchr(str, (int)'\n'); //改行コードを終端文字に変える
	if (p != NULL) {
		*p = '\0';
	}
	char *token;//一つずつ切り取っていく
	token = strtok(str, ",");
	strcpy(records[size].name, token);
	token = strtok(NULL, ",");
	strcpy(records[size].country, token);
	token = strtok(NULL, ",");
	records[size].short_score = atof(token);
	token = strtok(NULL, ",");
	records[size].free_score = atof(token);

	records[size].total_score = (records[size].free_score + records[size].short_score);
	size++;
}

BubbleSort(records, size);

int i;
for(i = 1; i < size; i++) {
	printf("%s %lf\n", records[i].name, records[i].total_score);
}

fclose(fp);
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
