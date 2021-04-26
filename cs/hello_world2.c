typedef unsigned short hword;
#define VRAM (hword *) 0x06000000
#define BGR(r, g, b) ((b << 10) + (g << 5) + r)
#include "8x8ascii.h"

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


int main(void) {
	
	/* GBA Display Mode Setting */
	*((hword *) 0x04000000) = 0x0F03;	/* Set Mode3 */

	cx = 8, cy = 9;		// �������W(8,9)����J�n
	
	locate(cx,cy);
	prints("Hello,World");	

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
