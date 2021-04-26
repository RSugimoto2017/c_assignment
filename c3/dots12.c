int main(void){
	unsigned short *ptr;
	unsigned short *ptr2;
	int i;
	int j;
	int push;

	ptr = 0x04000000;
	*ptr = 0x0F03;
	
	ptr2 = 0x04000130;
	j = 0;

	while(1){
		for (i = 0, ptr = 0x06000000; i < 240*160; i = i + 1) {
			*ptr = 0x7FFF;
			ptr = ptr + 1;
		}
		while (1){
			if ((*ptr2 & 0x0001) == 0x0001 && push == 1) {
				push = 0;
			}
			if ((*ptr2 & 0x0002) != 0x0002){
				j = 0 ;
				break;
			}
			if ((*ptr2 & 0x0001) != 0x0001 && push == 0) {
				j = j + 1;
				push = 1;
			}
			switch (j){
				case 1:
					for (i = 0, ptr = 0x06000000; i < 240*160; i = i + 1) {
						*ptr = 0x001F;
						ptr = ptr + 1;
					}
					continue;
				
				case 2:
					for (i = 0, ptr = 0x06000000; i < 240*160; i = i + 1) {
						*ptr = 0x03FF;
						ptr = ptr + 1;
					}
					continue;
					
				case 3:
					for (i = 0, ptr = 0x06000000; i < 240*160; i = i + 1) {
						*ptr = 0x7FE0;
						ptr = ptr + 1;
					}
					continue;
					
				case 4:
					for (i = 0, ptr = 0x06000000; i < 240*160; i = i + 1) {
						*ptr = 0x03E0;
						ptr = ptr + 1;
					}
					continue;
					
				case 5:
					for (i = 0, ptr = 0x06000000; i < 240*160; i = i + 1) {
						*ptr = 0x7C00;
						ptr = ptr + 1;
						j = 0;
					}
					continue;
			}
		}
	}return 0;
	
	while(1);			/* プログラム停止 */

	return 0;
}
