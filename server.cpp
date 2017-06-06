//--------------------------------------------------------------------------------
//  Code		: Depending on the incoming message, the server automatically send
//				  a response to the program
//  Subject		: Computer Network
//  Professor	: Sang Bang Choi
//  File		: Server.cpp
//--------------------------------------------------------------------------------

#include <stdio.h>			// Set to use printf() Function
#include <stdlib.h>			// Set to use exit() Function
#include <winsock2.h>		// Set to use a Socket (Using winsock.h or winsoch2.h)
#pragma comment (lib, "ws2_32.lib")

#define MAX_SIZE 64         // �ѹ��� ���� ������ ũ�⸦ �ִ� 64(Bytes)�� ���� 

void main(){   

	//Winsock_data ����(WSADATA type structure)
	WSADATA winsock_data; 
	//socket ����
	SOCKET Server_Socket; 
	// declare structure of socket address information.
	SOCKADDR_IN Server_Address; 
	// ������ ��Ʈ �ѹ� ����. 2000 ~ 65535���� ���������� ����
	unsigned short Server_Port = 6801;

	//Windows socket start ������, socket DLL files �ʱ�ȭ
	if(WSAStartup(0x202,&winsock_data) == SOCKET_ERROR){ 
		printf("WSAStartup Setting Error.\n");
		// Close initialization failure.
		WSACleanup();
		exit(0); 
	}
	
	// TCP�� ����ϹǷ� AF_INET ���
	Server_Address.sin_family = AF_INET;

	// IP address and connect port number
	// Test IP address : 127.0.0.1 (My computer internal IP address)
	Server_Address.sin_addr.s_addr = inet_addr("127.0.0.1");	// IP address
	Server_Address.sin_port = htons(Server_Port);				// Port Number

	// socket ����
	Server_Socket = socket(AF_INET, SOCK_STREAM,0);

	// socket ���� error��
	if(Server_Socket == INVALID_SOCKET){
		printf("Cannot create socket."); 
		closesocket( Server_Socket ); 
		WSACleanup(); 
		exit(0); 
	}

	if(bind(Server_Socket,(struct sockaddr*)&Server_Address,sizeof(Server_Address) ) == SOCKET_ERROR){ 
		printf("Cannot Bind."); 
		closesocket( Server_Socket );
		WSACleanup(); 
		exit(0); 
	} 

	printf(" >>  Server starting...  << \n\n"); 
	int count=1;

	// Loop
	while(1){

		if(listen(Server_Socket,SOMAXCONN) == SOCKET_ERROR){ 
			printf("listen Error.\n"); 
			closesocket(Server_Socket); 
			WSACleanup(); 
			exit(0); 
		}

		// Client Socket ����
		SOCKET Client_Socket;
		// Socket Address Structure declaration
		SOCKADDR_IN Client_Address;
		// Address size
		int AddressSize = sizeof(Client_Address);

		printf(" --------------------------------------------------------\n");
		// Connection Counting
		printf(" => Wait for Client(%d times).\n",count++); 

		// compare to Client Data and Server Data.
		if((Client_Socket = accept( Server_Socket,(struct sockaddr*)&Client_Address , &AddressSize )) == INVALID_SOCKET){ 
			printf("Accept Error.\n"); 
			getchar(); 
		} 
		else{ 
			printf(" => Connect IP: %s, Port : %d  Connect complete!\n\n", inet_ntoa(Client_Address.sin_addr), htons(Client_Address.sin_port)); 
		}
        int SendSize = MAX_SIZE;
		char x[MAX_SIZE]; //client�� ���� ���� ���� ù��° ����
		char Buffer_1[999]; //client�� ���� ù��°�� ���۹��� ��. x���� ����ֽ��ϴ�.
		recv(Client_Socket, Buffer_1, sizeof Buffer_1, 0); //x���� ���۹޽��ϴ�.
		printf("�Է¹��� x��: %s \n", x); //x���� ���
        send( Client_Socket,x, SendSize, 0 ); //������� char���� �����մϴ�.	     
      
	}
	// Wait : Server state is listen.
	getchar(); 
} 
