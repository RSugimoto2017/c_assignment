#include "gba1.h"

void display_time(hword);

int main(void) {
	
	volatile unsigned short time;

	/* ��ʏ��������[�`�� */
	*((unsigned short *)IOBASE) = 0xF03;

	/* �����\���ʒu�ݒ� */
	locate(1, 1);
	prints("Timer Program");
	
	locate(1, 3);
	prints("Time = ");
	
	/* �^�C�}�J�E���^�ݒ背�W�X�^ */
	*((unsigned short *)0x04000100) = 0xFF00;	// �^�C�}0 �J�E���^�ݒ�(���N���b�N1/2^24�b ��60n�b)
	*((unsigned short *)0x04000104) = 0xFF00;	// �^�C�}1 �J�E���^�ݒ�(���N���b�N1/2^16�b ��15.4u�b)
	*((unsigned short *)0x04000108) = 0xFF00;	// �^�C�}2 �J�E���^�ݒ�(���N���b�N1/2^8�b  ��3.93m�b)
	*((unsigned short *)0x0400010C) = 0x0000;	// �^�C�}3 �J�E���^�ݒ�(���N���b�N1�b)

	/* �^�C�}���䃌�W�X�^ */	
	*((unsigned short *)0x04000102) = 0x0080;	// �^�C�}0 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hOFF�C�v���X�P�[���Ȃ��j
	*((unsigned short *)0x04000106) = 0x0084;	// �^�C�}1 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
	*((unsigned short *)0x0400010A) = 0x0084;	// �^�C�}2 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
	*((unsigned short *)0x0400010E) = 0x0084;	// �^�C�}3 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
	
	while (1) {
		
		/* �^�C�}3 �J�E���g�l�Ǎ��� */
		time = 	*((unsigned short *)0x0400010C);
		
		/* time �\���ʒu�ݒ� */
		locate(8, 3);
		display_time(time);

	}
		
	return 0;

}

void display_time(hword val) {
	
	
/* ������10�i���Ƃ��ĕ\������֐��i�ő�l16�r�b�g�j*/

	byte char_data[] = "0123456789";
	byte buf[6];
	hword tmp;
	int i;
	
	/* ���͒lval�̌����ݒ� */
	i = 3;

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

