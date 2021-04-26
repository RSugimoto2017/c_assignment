#include "gba1.h"

void display_time(hword);

int main(void) {
	
	volatile unsigned short time;
	hword push = 0;
	hword a = 1;
	hword key_in;

	/* 画面初期化ルーチン */
	*((unsigned short *)IOBASE) = 0xF03;

	/* 文字表示位置設定 */
	locate(1, 1);
	prints("Timer Program");
	
	locate(1, 3);
	prints("Time = 0000");
	
	/* タイマカウンタ設定レジスタ */
	*((unsigned short *)0x04000100) = 0xFF00;	// タイマ0 カウンタ設定(元クロック1/2^24秒 約60n秒)
	*((unsigned short *)0x04000104) = 0xFF00;	// タイマ1 カウンタ設定(元クロック1/2^16秒 約15.4u秒)
	*((unsigned short *)0x04000108) = 0x0000;	// タイマ2 カウンタ設定(元クロック1/2^8秒  約3.93m秒)
	*((unsigned short *)0x0400010C) = 0x0000;	// タイマ3 カウンタ設定(元クロック1秒)

	/* タイマ制御レジスタ */	
	*((unsigned short *)0x04000102) = 0x0080;	// タイマ0 制御設定（タイマON，割込みOFF，カスケードOFF，プリスケーラなし）
	*((unsigned short *)0x04000106) = 0x0084;	// タイマ1 制御設定（タイマON，割込みOFF，カスケードON，プリスケーラなし）
	*((unsigned short *)0x0400010A) = 0x0004;	// タイマ2 制御設定（タイマON，割込みOFF，カスケードON，プリスケーラなし）
	*((unsigned short *)0x0400010E) = 0x0084;	// タイマ3 制御設定（タイマON，割込みOFF，カスケードON，プリスケーラなし）
	
	while (1) {
		
		/* キー入力 */
		hword key_in = ~(*(hword *) KEY_STATUS) & KEY_ALL;
		
		switch(key_in){
			case KEY_A:
				if((a == 0) && push == 0){
					a = 1;
					push = 1;
				}else if(a == 1 && push == 0){
					*((unsigned short *)0x0400010A) = 0x0084;
					a = 0;
					push = 1;
				}else if(a == 2 && push == 0){
					*((unsigned short *)0x0400010A) = 0x0084;
					push = 1;
					a = 0;
				}
				break;
			case KEY_B:
				a = 2;
				break;
			case 0x0000:
				push = 0;
				break;
		}
		
		switch(a) {
			case 0:				// 計測中
				/* タイマ3 カウント値読込み */
				time = *((unsigned short *)0x04000108);
				
				/* time 表示位置設定 */
				locate(8, 3);
				display_time(div(time, div(256, 10)));
					
				break;
			case 1:				// 一時停止
				*((unsigned short *)0x0400010A) = 0x0004;
				*((unsigned short *)0x04000108) = time;
				break;
			case 2:				// リセット
				*((unsigned short *)0x0400010A) = 0x0004;
				*((unsigned short *)0x04000108) = 0x0000;
				time = 0;

				locate(8, 3);
				display_time(time);

				break;
		}

	}
		
	return 0;

}

void display_time(hword val) {
	
	
/* 引数を10進数として表示する関数（最大値16ビット）*/

	byte char_data[] = "0123456789";
	byte buf[6];
	hword tmp;
	int i;
	
	/* 入力値valの桁数設定 */
	i = 3;

	/* 文字列の最後にNULLコード挿入 */
	buf[i+1] = 0;
	
	/* 最下位桁の文字（10で割った余り）を挿入し，入力値を10で割る */
	for(; i >= 0; i--) {
		buf[i] = char_data[mod(val, 10)];
		val = div(val, 10);
	}
	
	/* 文字列全体を表示 */
	prints(buf);
	
	return;
}

