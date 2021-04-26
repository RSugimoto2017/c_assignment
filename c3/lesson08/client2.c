//http://blog.livedoor.jp/akf0/archives/51585502.html

#include <stdio.h>

#include <winsock2.h>



int main(void) {	

	//接続するサーバの情報の構造体を用意

	struct sockaddr_in dest;

	memset(&dest, 0, sizeof(dest));

	//サーバの情報を入力
	
	char input[1024];
	char input2[1024];
	
	
	char destination[1000];  //サーバのアドレス(127.0.0.1は自分を指す)
	int port;
	
	printf("宛先のサーバアドレスを入力してください\n");
	scanf("%s", input);
	strcpy(destination, input);
	
	printf("宛先のポート番号を入力してください。\n");
	scanf("%s", input2);
	port = atoi(input2);

	dest.sin_port = htons(port);  //ポート番号

	dest.sin_family = AF_INET;

	dest.sin_addr.s_addr = inet_addr(destination);



	//ソケット通信の準備・生成

	WSADATA data;

	WSAStartup(MAKEWORD(2, 0), &data);

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);



	//サーバへの接続

	if (connect(s, (struct sockaddr *) &dest, sizeof(dest))) {

		printf("%sに接続できませんでした\n", destination);

		return -1;

	}

	printf("%sに接続しました\n", destination);

	char buffer[1024];
	
	while(1){
		
		char msg[1024];
		char input3[1024];
		
		printf("メッセージを入力してください。\n");
		scanf("%s", input3);
		strcpy(msg, input3);
		
		//printf("%s\n", msg);
	
		if(msg[0] == 'q'){
			break;
		}

		//サーバにデータを送信
		send(s, msg, strlen(msg), 0);

		//サーバからデータを受信
		recv(s, buffer, 1024, 0);

		printf("→ %s\n\n", buffer);
	}

	// Windows でのソケットの終了

	closesocket(s);

	WSACleanup();



	return 0;

}