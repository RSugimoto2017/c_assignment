typedef unsigned short hword;
#define RED	BGR(0x1F, 0x00, 0x00)
#define VRAM (hword *) 0x06000000
#define BGR(r, g, b) ((b << 10) + (g << 5) + r)

typedef struct {
	hword x;
	hword y;	
} point;

void draw_point(hword x, hword y, hword color);
void draw_line(point pa, point pb, hword color);

int main(void){

	hword *ptr;	

	ptr = (hword *) 0x04000000;		/* Mode Set Address */
	*ptr = 0x0F03;					/* Set Mode3 */
	
	point pa;
	pa.x = 30;
	pa.y = 20;

	point pb;
	pb.x = 130;
	pb.y = 120;

	draw_point(pa.x, pa.y, RED);
	draw_point(pb.x, pb.y, RED);
	draw_line(pa, pb, RED);
	
	while(1);
	
	return 0;
}


void draw_line(point pa, point pb, hword color){

	point pc;
	pc.x = (pa.x + pb.x) / 2;
	pc.y = (pa.y + pb.y) / 2;

	draw_point(pc.x, pc.y, RED);		

	if ((pc.x - pa.x) >= 1){
		draw_line(pa, pc, RED);
		draw_line(pc, pb, RED);
	}
	else {
		return;
	}
}

void draw_point(hword x, hword y, hword color) {

	hword *ptr;	

	ptr = VRAM;						/* VRAM Address(0,0) */
	ptr = ptr + x + (y * 240);		/* Display 240x160 */
	*ptr = color;
}
