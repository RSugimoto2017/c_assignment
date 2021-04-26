typedef unsigned short hword;
#define VRAM (hword *) 0x06000000
#define BGR(r, g, b) ((b << 10) + (g << 5) + r)
#include "8x8ascii.h"

/* 関数のプロトタイプ宣言 */
void locate(hword cx, hword cy);
void print_ascii(unsigned char ascii_num);
void draw_point (hword x, hword y, hword color);
void prints(unsigned char *str);
void printh(hword i);

/* 座標系の構造体宣言 */
typedef struct {
	hword x;		/* x coordinate for point */
	hword y;		/* y coordinate for point */
} point;

/* グローバル変数定義 */
point p;				// 座標指定用変数
hword cx = 0, cy = 0;	// 文字座標


int main(void) {
	
	/* GBA Display Mode Setting */
	*((hword *) 0x04000000) = 0x0F03;	/* Set Mode3 */

	locate(1,1);
	hword i = 42270;
	printh(i);

	while(1);
	
	return 0;

}


/* 文字座標(0, 0)～(29,19)の位置(cx, cy)を画面座標に変換する関数 */
void locate(hword cx, hword cy){
	if (cx < 30 ) {
		p.x = cx << 3;			/* x座標の指定 */
	} else {
		p.x = 30 - 1;			/* xの最大値を設定 */
	}
	if (cy < 20) {
		p.y = cy << 3;			/* y座標の指定 */
	} else {
		p.y = 20 - 1;			/* yの最大値を設定 */
	}
}



/* locateで設定された位置にASCIIコードascii_numに相当する文字を表示する関数 */
void print_ascii(unsigned char ascii_num) {
	
	hword tx, ty;							/* 文字パターンの座標指定 */
	unsigned char cbit;						/* ビット判定 */

	for (ty = 0; ty < 8; ty++) {			/* 文字パターンのy座標指定 */
	
		cbit = 0x80;						/* 判定ビットを8ビットの最上位にセット */
		
		for (tx = 0; tx < 8; tx++) {							/* 文字パターンのx座標指定 */
			if ((char8x8[ascii_num][ty] & cbit) == cbit){			/* ビット位置の判定 */
				draw_point((p.x + tx), (p.y + ty), BGR(0x1F, 0x1F, 0x1F));	// 1なら白
			} else {
				draw_point((p.x + tx), (p.y + ty), BGR(0x00, 0x00, 0x00));	// 0なら黒
			}
			cbit = cbit >> 1;					/* 判定ビットを1ビット右へシフト */
		}
	}
}


/* 指定した座標(x, y) に指定した色colorの点を描画する関数 */
void draw_point(hword x, hword y, hword color) {

	hword *ptr;	

	ptr = VRAM;				/* VRAM Address(0,0) */
	ptr = ptr + x + (y * 240);		/* Display 240x160 */
	*ptr = color;
}


/* 入力された文字列を順番に表示する関数 */
void prints(unsigned char *str) {
	while(*str != 0x00){
		print_ascii(*str);
		*str++;
		p.x = p.x + 8;
	}
}


/* 指定された数列を表示する関数 */
void printh(hword i) {
	unsigned char str1[4];

	int j;
	for(j = 0; i > 0; i = i / 16){
		str1[j] = i % 16;
		j++;
	} 
	
	prints("0x");
	
	for(j = 3; j >= 0; j--){
		if(str1[j] >= 10){
			print_ascii(str1[j] + 16 * 3 + 7);
			p.x = p.x + 8;
		}else{
			print_ascii(str1[j] + 16 * 3);
			p.x = p.x + 8;
		}
	}
	
}

