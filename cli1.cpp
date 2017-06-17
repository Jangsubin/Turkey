#include <stdio.h>
#include <winsock.h>
#include <string.h>

#pragma comment (lib, "ws2_32.lib")		// Linker 를 위한 컴파일러 옵션

#define PORT 5000						// 기본은 로컬 IP 의 포트 번호 5000 번
//#define IP "172.30.1.59"					// 로컬 = 127.0.0.1

int main(void)
{
	// 윈속 초기화

	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		fprintf(stderr, "WSAStartup 오류\n");
		return 1;

	}

	// 소켓 구조체 완성
	// TCP

	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == SOCKET_ERROR)
	{
		fprintf(stderr, "socket() 함수 오류\n");
		WSACleanup();
		return 1;

	}

	// TCP 연결에 필요한 주소 구조체 완성

	
	char str1[10];
	printf("문자열을 입력하세요 : ");
	scanf("%s", str1);
	
	sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(str1);
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	// 서버에 접속

	if (connect(s, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("connect() 오류\n");
		closesocket(s);
		WSACleanup();
		return 1;

	}

	// 파일 크기를 받음

	int ret;
	char buff[1024];

	if ((ret = recv(s, buff, 1024, 0)) == SOCKET_ERROR)
	{
		printf("Socket Error : 파일을 받지 못했습니다.\n");
		closesocket(s);
		WSACleanup();

		return 1;

	}

	else

	{

		// 파일을 받음

		FILE *fp;
		if ((fp = fopen("write.jpg", "wb")) == NULL)			// write.jpg 파일을 2진 쓰기 용으로 열기
		{
			printf("write.jpg 파일 생성을 할수 없습니다.\n");
			fclose(fp);
			closesocket(s);
			WSACleanup();
			return 1;

		}

		long fsize = atol(buff);
		char* recvbuff;
		recvbuff = new char[fsize];			// 동적 할당으로 메모리 낭비 줄임

		if ((ret = recv(s, recvbuff, fsize, 0)) == SOCKET_ERROR)
		{
			printf("recv : 전송중 문제가 발생했습니다.\n");
			fclose(fp);
			closesocket(s);
			WSACleanup();
			return 1;
		}


		else
		{

			// 다 받았을때 파일 크기 만큼 다시 전송

			fwrite(recvbuff, sizeof(char), fsize, fp);

			_ltoa_s(fsize, buff, 10);

			ret = send(s, buff, sizeof(buff), 0);

			printf("%ld 바이트를 받았습니다.\n", fsize);

			fflush(fp);
			fclose(fp);
			delete recvbuff;


		}


	}

	// 파일, 소켓을 닫습니다

	closesocket(s);
	WSACleanup();
	return 0;

}