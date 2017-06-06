
#include <stdio.h>			
#include <stdlib.h>			
#include <winsock2.h>		
#pragma comment (lib, "ws2_32.lib")

#define MAX_SIZE 64         

void main(){   

	
	WSADATA winsock_data; 
	SOCKET Server_Socket; 
	SOCKADDR_IN Server_Address; 
	unsigned short Server_Port = 6801;
	if(WSAStartup(0x202,&winsock_data) == SOCKET_ERROR){ 
		printf("WSAStartup Setting Error.\n");
		WSACleanup();
		exit(0); 
	}
	Server_Address.sin_family = AF_INET;
	Server_Address.sin_addr.s_addr = inet_addr("127.0.0.1");	
	Server_Address.sin_port = htons(Server_Port);				

	Server_Socket = socket(AF_INET, SOCK_STREAM,0);

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


	while(1){

		if(listen(Server_Socket,SOMAXCONN) == SOCKET_ERROR){ 
			printf("listen Error.\n"); 
			closesocket(Server_Socket); 
			WSACleanup(); 
			exit(0); 
		}
	
		SOCKET Client_Socket;
		SOCKADDR_IN Client_Address;	
		int AddressSize = sizeof(Client_Address);

		printf(" --------------------------------------------------------\n");	
		printf(" => Wait for Client(%d times).\n",count++); 

	
		if((Client_Socket = accept( Server_Socket,(struct sockaddr*)&Client_Address , &AddressSize )) == INVALID_SOCKET){ 
			printf("Accept Error.\n"); 
			getchar(); 
		} 
		else{ 
			printf(" => Connect IP: %s, Port : %d  Connect complete!\n\n", inet_ntoa(Client_Address.sin_addr), htons(Client_Address.sin_port)); 
		}
        int SendSize = MAX_SIZE;
		char x[MAX_SIZE];
		char Buffer_1[999]; 
		recv(Client_Socket, x,SendSize, 0); 
		printf(" x value: %s \n", x);
        send( Client_Socket,x, SendSize, 0 );  
      
	}
	getchar(); 
} 
