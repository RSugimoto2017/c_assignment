typedef unsigned short hword;
#define WHITE	BGR(0x1F, 0x1F, 0x1F)
#define BLACK	BGR(0x00, 0x00, 0x00)
#define VRAM (hword *) 0x06000000
#define BGR(r, g, b)((b << 10) + (g << 5) + r)

unsigned char zero[8] = {0x78,0xCC,0xDC,0xFC,0xEC,0xCC,0x78,0x00};

void draw_point(hword x, hword y, hword color);

int main(void){
	
	hword *ptr;
	int i, j, k;
	hword x, y;
	
	ptr = (hword *) 0x04000000;	 
	*ptr = 0x0F03;		 

	x = 0;
	y = 0;
	k = 128;
	for(j = 0; j<8; j++){
		for(i = 0; i<8; i++){
			if(zero[j] - k>=0){
				draw_point(x, y, WHITE);
				zero[j] = zero[j] - k;
			}
			x++;
			k = k/2;
		}
		x = 0;	
		y++;
		k = 128;
	}

	while(1);		

	return 0;
}

void draw_point(hword x, hword y, hword color) {

	hword *ptr;	

	ptr = VRAM;
	ptr = ptr + x + (y * 240);		
	*ptr = color;
}

