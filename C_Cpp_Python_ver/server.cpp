#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "main.h"

using namespace std;

#define BUF_LEN 1024
#define PORT 8080

static struct sockaddr_in server_addr, client_addr;
static int server_fd, client_fd, n, n2;
static char recv_data[BUF_LEN];


int socketReceive()
{
	char chat_data[BUF_LEN];
	char temp[20];
	int len;

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		cout << "Server: can not Open Socket" << endl;
		return 1;
	}

	memset(&server_addr, 0x00, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr*) & server_addr, sizeof(server_addr)) < 0)
	{
		cout << "Server: cat not bind local addrss" << endl;
		return 1;

	}


	if (listen(server_fd, 5) < 0)
	{
		cout << "Server: cat not listen connnect" << endl;
		return 1;
	}


	memset(recv_data, 0x00, sizeof(recv_data));
	len = sizeof(client_addr);
	cout << "=====[PORT] : " << PORT << "=====" << endl;
	//cout << "Server : wating connection request" << endl;


	while (1)
	{
		client_fd = accept(server_fd, (struct sockaddr*) & client_addr, (socklen_t*)&len);

		if (client_fd < 0)
		{
			cout << "Server: accept failed" << endl;
			return 0;
		}

		inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
		//cout << "Server: " << temp << " client connect" << endl;

		//cout << "IP : " << inet_ntoa(client_addr.sin_addr) << " PROT : " << ntohs(client_addr.sin_port) << endl;
		while (1)
		{

			if ((n = recv(client_fd, recv_data, sizeof(recv_data), 0)) == -1)
			{
				//cout << inet_ntoa(client_addr.sin_addr)<< " ("<< ntohs(client_addr.sin_port)<<") "<<" disconnect" << endl;
				close(client_fd);
				break;
			}
			else if (n > 0)
			{
				recv_data[n] = '\0';
				//printf("\n%s(%d) %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), recv_data);
				string name = recv_data;
				doorOpenSt(name);
				break;
			}
		}

		close(client_fd);
		// printf("Server: %s client closed.\n", temp);

	}

	close(server_fd);

	return 0;
}