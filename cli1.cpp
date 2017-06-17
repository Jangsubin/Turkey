#include <stdio.h>
#include <winsock.h>
#include <string.h>

#pragma comment (lib, "ws2_32.lib")		// Linker �� ���� �����Ϸ� �ɼ�

#define PORT 5000						// �⺻�� ���� IP �� ��Ʈ ��ȣ 5000 ��
//#define IP "172.30.1.59"					// ���� = 127.0.0.1

int main(void)
{
	// ���� �ʱ�ȭ

	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		fprintf(stderr, "WSAStartup ����\n");
		return 1;

	}

	// ���� ����ü �ϼ�
	// TCP

	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == SOCKET_ERROR)
	{
		fprintf(stderr, "socket() �Լ� ����\n");
		WSACleanup();
		return 1;

	}

	// TCP ���ῡ �ʿ��� �ּ� ����ü �ϼ�

	
	char str1[10];
	printf("���ڿ��� �Է��ϼ��� : ");
	scanf("%s", str1);
	
	sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(str1);
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	// ������ ����

	if (connect(s, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("connect() ����\n");
		closesocket(s);
		WSACleanup();
		return 1;

	}

	// ���� ũ�⸦ ����

	int ret;
	char buff[1024];

	if ((ret = recv(s, buff, 1024, 0)) == SOCKET_ERROR)
	{
		printf("Socket Error : ������ ���� ���߽��ϴ�.\n");
		closesocket(s);
		WSACleanup();

		return 1;

	}

	else

	{

		// ������ ����

		FILE *fp;
		if ((fp = fopen("write.jpg", "wb")) == NULL)			// write.jpg ������ 2�� ���� ������ ����
		{
			printf("write.jpg ���� ������ �Ҽ� �����ϴ�.\n");
			fclose(fp);
			closesocket(s);
			WSACleanup();
			return 1;

		}

		long fsize = atol(buff);
		char* recvbuff;
		recvbuff = new char[fsize];			// ���� �Ҵ����� �޸� ���� ����

		if ((ret = recv(s, recvbuff, fsize, 0)) == SOCKET_ERROR)
		{
			printf("recv : ������ ������ �߻��߽��ϴ�.\n");
			fclose(fp);
			closesocket(s);
			WSACleanup();
			return 1;
		}


		else
		{

			// �� �޾����� ���� ũ�� ��ŭ �ٽ� ����

			fwrite(recvbuff, sizeof(char), fsize, fp);

			_ltoa_s(fsize, buff, 10);

			ret = send(s, buff, sizeof(buff), 0);

			printf("%ld ����Ʈ�� �޾ҽ��ϴ�.\n", fsize);

			fflush(fp);
			fclose(fp);
			delete recvbuff;


		}


	}

	// ����, ������ �ݽ��ϴ�

	closesocket(s);
	WSACleanup();
	return 0;

}