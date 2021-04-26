typedef unsigned short hword;
#define VRAM (hword *) 0x06000000
#define BGR(r, g, b) ((b << 10) + (g << 5) + r)
#include "8x8ascii.h"

void draw_point (hword x, hword y, hword color);
hword locate(hword x, hword y);
void print_ascii(unsigned char ascii_num);

hword X = 0;
hword Y = 0;
hword color1 = BGR(0x1F, 0x1F, 0x1F); 	/* 白 */
hword color2 = BGR(0x00, 0x00, 0x00); 	/* 黒 */

int main(void) {

	hword *ptr;	
	
	/* GBA Display Mode Setting */
	ptr = (hword *) 0x04000000;		/* Mode Set Address */
	*ptr = 0x0F03;					/* Set Mode3 */

	locate(9,9);
	print_ascii(72);

	locate(10,9);
	print_ascii(101);

	locate(11,9);
	print_ascii(108);

	locate(12,9);
	print_ascii(108);

	locate(13,9);
	print_ascii(111);

	locate(15,9);
	print_ascii(87);

	locate(16,9);
	print_ascii(111);

	locate(17,9);
	print_ascii(114);

	locate(18,9);
	print_ascii(108);

	locate(19,9);
	print_ascii(100);

	locate(20,9);
	print_ascii(33);
	
	while(1);
	
	return 0;
}


void draw_point(hword x, hword y, hword color) {

	hword *ptr;	

	ptr = VRAM;						/* VRAM Address(0,0) */
	ptr = ptr + x + (y * 240);				/* Display 240x160 */
	*ptr = color;
}

hword locate (hword x, hword y){
	
	X = x * 8;
	Y = y * 8;	
}

void print_ascii(unsigned char ascii_num){
	
	unsigned char cbit; 				/* ビット判定 */
	hword tx, ty;					/* 文字パターンの座標指定 */
	
	for (ty = 0; ty < 8; ty++) {			/* 文字パターンのy座標指定 */
		cbit = 0x80;				/* 判定ビットを8ビットの最上位に */
		
		for (tx = 0; tx < 8; tx++) {		/* 文字パターンのx座標指定 */
			if ((char8x8[ascii_num][ty] & cbit) == cbit){
				draw_point(X + tx, Y + ty, color1);		// 1なら白
			} else {
				draw_point(X + tx, Y + ty, color2);		// 0なら黒
			}
			cbit = cbit >> 1;				/* 判定ビットを1ビット右へシフト */
		}
	}


}

