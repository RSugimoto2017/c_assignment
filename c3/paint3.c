int main(void){
	unsigned short *ptr;
	unsigned short *ptr2;
	int i;

	ptr = 0x04000000;
	*ptr = 0x0F03;
	
	ptr2 = 0x04000130;

	while(1){

		if((*ptr2 & 0x0002) != 0x0002){
			break;
		}else if((*ptr2 & 0x0001) != 0x0001){
			continue;
		}else{ 

			for (i = 0, ptr = 0x06000000; i < 240*160; i = i + 1) {
				if(i <= 240 * 53){
					*ptr = 0x0000;
					ptr = ptr + 1;
				}else if(240 * 53 < i && i <= 240 * 107){
					*ptr = 0x001F;
					ptr = ptr + 1;
				}else if(240 * 107 < i){
					*ptr = 0x03FF;
					ptr = ptr + 1;
				} 
			}
			for(i = 0; i < 500000; i = i + 1){
			}
		}

		if((*ptr2 & 0x0002) != 0x0002){
			break;
		}else if((*ptr2 & 0x0001) != 0x0001){
			continue;
		}else{

			for (i = 0, ptr = 0x06000000; i < 240*160; i = i + 1) {
				if(i <= 240 * 53){
					*ptr = 0x001F;
					ptr = ptr + 1;
				}else if(240 * 53 < i && i <= 240 * 107){
					*ptr = 0x7FFF;
					ptr = ptr + 1;
				}else if(240 * 107 < i){
					*ptr = 0x7C00;
					ptr = ptr + 1;
				} 
			}
			for(i = 0; i < 500000; i = i + 1){
			}

		}


	}
	for (i = 0, ptr = 0x06000000; i < 240*160; i = i + 1) {
			*ptr = 0x7FFF;
			ptr = ptr + 1;
	}
	while(1);			/* プログラム停止 */

	return 0;
}
