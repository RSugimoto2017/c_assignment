typedef unsigned short hword;
#define WHITE	BGR(0x1F, 0x1F, 0x1F)
#define VRAM (hword *) 0x06000000
#define BGR(r, g, b)((b << 10) + (g << 5) + r)

unsigned char zero[8][8] = {
		{ 0, 1, 1, 1, 1, 0, 0, 0 },
		{ 1, 1, 0, 0, 1, 1, 0, 0 },
		{ 1, 1, 0, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 0, 1, 1, 0, 0 },
		{ 1, 1, 0, 0, 1, 1, 0, 0 },
		{ 0, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
		};

void draw_point(hword x, hword y, hword color);

int main(void){
	
	hword *ptr;
	int i, j;
	hword x, y;
	
	ptr = (hword *) 0x04000000;	 
	*ptr = 0x0F03;		 

	x = 0;
	y = 0;

	for(i = 0; i<8; i++){
		for(j = 0; j<8; j++){
			if(zero[i][j] == 1){
				draw_point(x, y, WHITE);
				}
			x++;
			}
		x = 0;
		y++;
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

