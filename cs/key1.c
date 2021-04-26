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

/* �֐��̃v���g�^�C�v�錾 */
void locate(hword cx, hword cy);
void print_ascii(unsigned char ascii_num);
void draw_point (hword x, hword y, hword color);
void prints(unsigned char *str);

/* ���W�n�̍\���̐錾 */
typedef struct {
	hword x;		/* x coordinate for point */
	hword y;		/* y coordinate for point */
} point;

/* �O���[�o���ϐ���` */
point p;				// ���W�w��p�ϐ�
hword cx = 0, cy = 0;	// �������W
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


/* �������W(0, 0)�`(29,19)�̈ʒu(cx, cy)����ʍ��W�ɕϊ�����֐� */
void locate(hword cx, hword cy){
	if (cx < 30 ) {
		p.x = cx << 3;			/* x���W�̎w�� */
	} else {
		p.x = 30 - 1;			/* x�̍ő�l��ݒ� */
	}
	if (cy < 20) {
		p.y = cy << 3;			/* y���W�̎w�� */
	} else {
		p.y = 20 - 1;			/* y�̍ő�l��ݒ� */
	}
}



/* locate�Őݒ肳�ꂽ�ʒu��ASCII�R�[�hascii_num�ɑ������镶����\������֐� */
void print_ascii(unsigned char ascii_num) {
	
	hword tx, ty;							/* �����p�^�[���̍��W�w�� */
	unsigned char cbit;						/* �r�b�g���� */

	for (ty = 0; ty < 8; ty++) {			/* �����p�^�[����y���W�w�� */
	
		cbit = 0x80;						/* ����r�b�g��8�r�b�g�̍ŏ�ʂɃZ�b�g */
		
		for (tx = 0; tx < 8; tx++) {							/* �����p�^�[����x���W�w�� */
			if ((char8x8[ascii_num][ty] & cbit) == cbit){			/* �r�b�g�ʒu�̔��� */
				draw_point((p.x + tx), (p.y + ty), BGR(0x1F, 0x1F, 0x1F));	// 1�Ȃ甒
			} else {
				draw_point((p.x + tx), (p.y + ty), BGR(0x00, 0x00, 0x00));	// 0�Ȃ獕
			}
			cbit = cbit >> 1;					/* ����r�b�g��1�r�b�g�E�փV�t�g */
		}
	}
}


/* �w�肵�����W(x, y) �Ɏw�肵���Fcolor�̓_��`�悷��֐� */
void draw_point(hword x, hword y, hword color) {

	hword *ptr;	

	ptr = VRAM;						/* VRAM Address(0,0) */
	ptr = ptr + x + (y * 240);		/* Display 240x160 */
	*ptr = color;
}


/* �w�肳�ꂽ����������Ԃɕ\������֐� */
void prints(unsigned char *str) {
	while(*str != 0x00){
		print_ascii(*str);
		*str++;
		p.x = p.x + 8;
	}
}

