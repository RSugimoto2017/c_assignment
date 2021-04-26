typedef unsigned short hword;
#define VRAM (hword *) 0x06000000
#define BGR(r, g, b) ((b << 10) + (g << 5) + r)
#include "8x8ascii.h"

#define KEY_A 		1<<0
#define KEY_B	 	1<<1
#define KEY_RIGHT	1<<4
#define KEY_LEFT 	1<<5
#define KEY_UP	1<<6
#define KEY_DOWN 	1<<7

/* 関数のプロトタイプ宣言 */
void locate(hword cx, hword cy);
void print_ascii_white(unsigned char ascii_num);
void print_ascii_yellow(unsigned char ascii_num);
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
hword mode = 1;
hword push = 0;
hword ascii_num = 0;
unsigned int flag[20][30] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


int main(void) {
	
	/* GBA Display Mode Setting */
	*((hword *) 0x04000000) = 0x0F03;	/* Set Mode3 */

	hword *ptr2;
	ptr2=(hword*)0x04000130;

	while (1) {

		int wx, wy;
		for(wy = 0; wy < 20; wy++){
			for(wx = 0; wx < 30; wx++){
				if(flag[wy][wx] != 0){
					locate(wx, wy);
					print_ascii_yellow (flag[wy][wx]);
				}
			}
		}
	
		key = ~*ptr2 & 0x03FF;

		switch(key) {
			case KEY_A:
				if(mode != 1){
					mode = 1;											locate(cx,cy);
					prints("_");
				}
				break;
			case KEY_B:
				if(mode != 2){
					mode = 2;
				}
				break;
		}
		/*移動モード*/
		switch(mode){
			case 1:
				ascii_num = 65;
				
				key = ~*ptr2 & 0x03FF;
					locate(cx,cy);
					prints("_");
	
				if(key == KEY_RIGHT && push == 0 && cx < 29){
					locate(cx,cy);
					print_ascii_white(0);
					cx++;
					locate(cx,cy);
					prints("_");
					push = 1;
				}else if(key == KEY_LEFT && push == 0 && 0 < cx){
					locate(cx,cy);
					print_ascii_white(0);
					cx--;
					locate(cx,cy);
					prints("_");
					push = 1;
				}else if(key == KEY_UP && push == 0 && 0 < cy){
					locate(cx,cy);					
					print_ascii_white(0);
					cy--;
					locate(cx,cy);
					prints("_");
					push = 1;
				}else if(key == KEY_DOWN && push == 0 && cy < 19){
					locate(cx,cy);
					print_ascii_white(0);
					cy++;
					locate(cx,cy);
					prints("_");
					push = 1;
				}else if(key == 0x0000){
					push = 0;
				}else{
				}
				break;	
			/*文字選択モード*/	
			case 2:
						
	
				key = ~*ptr2 & 0x03FF;
	
				if(key == KEY_UP && push == 0){
					ascii_num--;
					if(ascii_num < 0){
						ascii_num = 255;
					}
					locate(cx, cy);
					print_ascii_yellow(ascii_num);
					push = 1;
				}else if(key == KEY_DOWN && push == 0){
					ascii_num++;
					if(255 < ascii_num){
						ascii_num = 0;
					}
					locate(cx, cy);
					print_ascii_yellow(ascii_num);
					push = 1;
					
				}else if(key == 0x0000){
					push = 0;
					flag [cy][cx] = ascii_num;
				}else{
				}
				break;			
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



/* locateで設定された位置にASCIIコードascii_numに相当する文字を白色で表示する関数 */
void print_ascii_white(unsigned char ascii_num) {
	
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

/* locateで設定された位置にASCIIコードascii_numに相当する文字を黄色で表示する関数 */
void print_ascii_yellow(unsigned char ascii_num) {
	
	hword tx, ty;							/* 文字パターンの座標指定 */
	unsigned char cbit;						/* ビット判定 */

	for (ty = 0; ty < 8; ty++) {			/* 文字パターンのy座標指定 */
	
		cbit = 0x80;						/* 判定ビットを8ビットの最上位にセット */
		
		for (tx = 0; tx < 8; tx++) {							/* 文字パターンのx座標指定 */
			if ((char8x8[ascii_num][ty] & cbit) == cbit){			/* ビット位置の判定 */
				draw_point((p.x + tx), (p.y + ty), BGR(0x1F, 0x1F, 0x00));	// 1なら黄色
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
/* 指定された文字列を順番に表示する関数(白色) */
void prints(unsigned char *str) {
	while(*str != 0x00){
		print_ascii_white(*str);
		*str++;
		p.x = p.x + 8;
	}
}

