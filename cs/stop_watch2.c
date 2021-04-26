#include "gba1.h"

void display_time(hword);

int main(void) {
	
	volatile unsigned short time;
	hword push = 0;
	hword a = 1;
	hword key_in;
	hword minute;
 	hword second;
	hword subsecond = 1;
	hword s_byo;

	/* ��ʏ��������[�`�� */
	*((unsigned short *)IOBASE) = 0xF03;

	/* �����\���ʒu�ݒ� */
	locate(1, 1);
	prints("Stop Watch Program");
	
	locate(1, 3);
	prints("Time = 00:00.0 sec");
	
	/* �^�C�}�J�E���^�ݒ背�W�X�^ */
	*((unsigned short *)0x04000100) = 0xFF00;	// �^�C�}0 �J�E���^�ݒ�(���N���b�N1/2^24�b ��60n�b)
	*((unsigned short *)0x04000104) = 0xFF00;	// �^�C�}1 �J�E���^�ݒ�(���N���b�N1/2^16�b ��15.4u�b)
	*((unsigned short *)0x04000108) = 0x0000;	// �^�C�}2 �J�E���^�ݒ�(���N���b�N1/2^8�b  ��3.93m�b)
	*((unsigned short *)0x0400010C) = 0x0000;	// �^�C�}3 �J�E���^�ݒ�(���N���b�N1�b)

	/* �^�C�}���䃌�W�X�^ */	
	*((unsigned short *)0x04000102) = 0x0080;	// �^�C�}0 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hOFF�C�v���X�P�[���Ȃ��j
	*((unsigned short *)0x04000106) = 0x0084;	// �^�C�}1 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
	*((unsigned short *)0x0400010A) = 0x0004;	// �^�C�}2 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
	*((unsigned short *)0x0400010E) = 0x0084;	// �^�C�}3 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
	
	while (1) {
		
		/* �L�[���� */
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
			case 0:				// �v����
				/* �^�C�}3 �J�E���g�l�Ǎ��� */
				time = *((unsigned short *)0x04000108);

				s_byo = div(time, div(256, 10));
				second = div(s_byo, 10);
				subsecond = mod(s_byo, 10);
				if (mod(second, 60) == 0) {
					second = 0;
					minute = minute + 1;
				}
				minute = div(s_byo, 600);

				
				/* time �\���ʒu�ݒ� */
				locate(8, 3);
				display_time(minute);
				locate(11, 3);
				display_time(mod(second, 60));
				locate(14, 3);
				print_ascii(subsecond + 48);
				
				break;

			case 1:				// �ꎞ��~
				*((unsigned short *)0x0400010A) = 0x0004;
				*((unsigned short *)0x04000108) = time;
				break;
			case 2:				// ���Z�b�g
				*((unsigned short *)0x0400010A) = 0x0004;
				*((unsigned short *)0x04000108) = 0x0000;
				time = 0;

				locate(1, 3);
				prints("Time = 00:00.0 sec");

				break;
		}

	}
		
	return 0;

}

void display_time(hword val) {
	
	
/* ������10�i���Ƃ��ĕ\������֐��i�ő�l16�r�b�g�j*/

	byte char_data[] = "0123456789";
	byte buf[1];
	hword tmp;
	int i;
	
	/* ���͒lval�̌����ݒ� */
	i = 1;

	/* ������̍Ō��NULL�R�[�h�}�� */
	buf[i+1] = 0;
	
	/* �ŉ��ʌ��̕����i10�Ŋ������]��j��}�����C���͒l��10�Ŋ��� */
	for(; i >= 0; i--) {
		buf[i] = char_data[mod(val, 10)];
		val = div(val, 10);
	}
	
	/* ������S�̂�\�� */
	prints(buf);
	
	return;
}

