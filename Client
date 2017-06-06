
#include <stdio.h>			
#include <stdlib.h>			
#include <winsock2.h>		
#pragma comment (lib, "ws2_32.lib")
 
#define MAX_SIZE 64		

void main(){ 

	WSADATA winsock_data;

	SOCKET Client_Socket; 

	SOCKADDR_IN Server_Address; 

	unsigned short Server_Port = 6801;
	int ReturnVal; 


	if(WSAStartup(0x202,&winsock_data) == SOCKET_ERROR){
		printf( "WSAStartup Setting Error.\n" );
		// Close initialization failure.
		WSACleanup();
		exit(0);
	}

	int count=1;	
  
	char SendMessage[MAX_SIZE];
	char Tmp[MAX_SIZE]="Off"; 
	

	while(strcmp(SendMessage,Tmp) != 0){
	
		Client_Socket = socket(AF_INET, SOCK_STREAM,0);


		if( Client_Socket == INVALID_SOCKET ){ 
			printf("Create Socket Error.");
			WSACleanup(); 
			exit(0);
		}


		Server_Address.sin_family = AF_INET;


		Server_Address.sin_addr.s_addr = inet_addr("127.0.0.1");	// IP address
		Server_Address.sin_port = htons(Server_Port);				// Port Number

		// Attempts to connect to the server.
		ReturnVal = connect(Client_Socket, (struct sockaddr*)&Server_Address, sizeof(Server_Address));

		printf("\n --------------------------------------------------------\n");

		// if ReturnVal is 1, Connection setup error.
		if(ReturnVal){ 
			printf(" >>  Server Connection Error.  << \n\n");
			closesocket(Client_Socket); 
			WSACleanup(); 
			exit(0); 
		}
		else{ 
			// Count the number of connections.
			printf(" >> connected to the server( %d times ).  << \n\n",count++);
		}

		int SendSize = MAX_SIZE; 
		char x[MAX_SIZE]; 
		printf("GIVE me value of x "); 
		scanf("%s", &x); 
		send(Client_Socket, x, SendSize, 0); 
		printf("result : %s \n", x); 
	}//while end.

	closesocket(Client_Socket);
	WSACleanup();
	
	// Wait
	getchar();
}


