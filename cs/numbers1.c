typedef unsigned short hword;
#define VRAM (hword *) 0x06000000
#define BGR(r, g, b) ((b << 10) + (g << 5) + r)
#include "8x8ascii.h"

void draw_point (hword x, hword y, hword color);
void draw_word (hword x, hword y, hword n, hword color1, hword color2);

int main(void) {

	hword *ptr;	
	hword n;
	static hword x = 0;
	static hword y = 0;
	hword color1 = BGR(0x1F, 0x1F, 0x1F); 	/* 白 */
	hword color2 = BGR(0x00, 0x00, 0x00); 	/* 黒 */
	
	/* GBA Display Mode Setting */
	ptr = (hword *) 0x04000000;		/* Mode Set Address */
	*ptr = 0x0F03;					/* Set Mode3 */

	for(n=48; n<58; n++){
		draw_word(x, y, n,color1,color2);
		x = x + 8;
		if(x >= 232){
			x = 0;
			y = y + 8;
		}
	}
	
	while(1);
	
	return 0;
}


void draw_point(hword x, hword y, hword color) {

	hword *ptr;	

	ptr = VRAM;						/* VRAM Address(0,0) */
	ptr = ptr + x + (y * 240);				/* Display 240x160 */
	*ptr = color;
}

void draw_word(hword x, hword y, hword n, hword color1, hword color2) {

	unsigned char cbit; 				/* ビット判定 */
	hword tx, ty;					/* 文字パターンの座標指定 */
	
	for (ty = 0; ty < 8; ty++) {			/* 文字パターンのy座標指定 */
		cbit = 0x80;				/* 判定ビットを8ビットの最上位に */
		
		for (tx = 0; tx < 8; tx++) {		/* 文字パターンのx座標指定 */
			if ((char8x8[n][ty] & cbit) == cbit){
				draw_point(tx + x, ty + y, color1);		// 1なら白
			} else {
				draw_point(tx + x, ty + y, color2);		// 0なら黒
			}
			cbit = cbit >> 1;				/* 判定ビットを1ビット右へシフト */
		}
	}
}