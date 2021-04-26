typedef unsigned short hword;
#define VRAM (hword *) 0x06000000
#define BGR(r, g, b) ((b << 10) + (g << 5) + r)
#include "8x8ascii.h"

#define KEY_A 		1<<0
#define KEY_B	 	1<<1
#define KEY_SELECT 	1<<2
#define KEY_START 	1<<3
#define KEY_RIGHT	1<<4
#define KEY_LEFT 	1<<5
#define KEY_UP		1<<6
#define KEY_DOWN 	1<<7
#define KEY_R 		1<<8
#define KEY_L 		1<<9

/* 関数のプロトタイプ宣言 */
void locate(hword cx, hword cy);
void print_ascii(unsigned char ascii_num);
void draw_point (hword x, hword y, hword color);
void prints(unsigned char *str);

/* 座標系の構造体宣言 */
typedef struct {
	hword x;		/* x coordinate for point */
	hword y;		/* y coordinate for point */
} point;

/* グローバル変数定義 */
point p;				// 座標指定用変数
hword cx = 0, cy = 0;	// 文字座標
hword key;


int main(void) {
	
	/* GBA Display Mode Setting */
	*((hword *) 0x04000000) = 0x0F03;	/* Set Mode3 */

	cx = 1, cy = 1;
	locate(cx, cy);
	prints("Press Any Key!");	
	cy = 2;

	hword *ptr2;
	ptr2=(hword*)0x04000130;

while (1) {

		key = ~*ptr2 & 0x03FF;
		locate(cx,cy);
		prints("Pressed Key =");
		
		switch(key){
			case KEY_A:	 prints("A     ");	break;
				
			case KEY_B:	 prints("B     ");	break;
			
			case KEY_SELECT: prints("SELECT");	break;
				
			case KEY_START:  prints("START ");	break;
			
			case KEY_RIGHT:	 prints("RIGHT ");	break;
				
			case KEY_LEFT:	 prints("LEFT  ");	break;
				
			case KEY_UP:	 prints("UP    ");	break;
				
			case KEY_DOWN:	 prints("DOWN  ");	break;
			
			case KEY_R:	 prints("R     ");	break;
				
			case KEY_L:	 prints("L     ");	break;
				
			default:	 prints("      ");	break;
		}
}

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

	ptr = VRAM;						/* VRAM Address(0,0) */
	ptr = ptr + x + (y * 240);		/* Display 240x160 */
	*ptr = color;
}


/* 指定された文字列を順番に表示する関数 */
void prints(unsigned char *str) {
	while(*str != 0x00){
		print_ascii(*str);
		*str++;
		p.x = p.x + 8;
	}
}

