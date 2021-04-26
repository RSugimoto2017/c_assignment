#include<stdio.h>
int main(void){
	char str[] = "apple";

	printf("str[] = %s の各文字とアドレスは以下の通りである\n", str);
	printf("str[0] = %c, adress = %p\n",str[0], &str[0] );
	printf("str[1] = %c, adress = %p\n",str[1], &str[1] );
	printf("str[2] = %c, adress = %p\n",str[2], &str[2] );
	printf("str[3] = %c, adress = %p\n",str[3], &str[3] );
	printf("str[4] = %c, adress = %p\n",str[4], &str[4] );

	printf("したがって、文字列の各文字は、連続したメモリ領域に記録されている。\n");

	printf("また、strのアドレスは、str = %pである。\n", str);
	printf("したがって、strは先頭の文字アドレスを指す。\n");
}
