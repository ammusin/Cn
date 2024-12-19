#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = {0};

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	listen(server_fd, 3);
	
	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

	while(1){

		memset(buffer, 0, BUFFER_SIZE);
        	int valread = read(new_socket, buffer, BUFFER_SIZE);
        	if (valread <= 0) break;

        	printf("Client: %s\n", buffer);

        	char *response = "Message received";
        	send(new_socket, response, strlen(response), 0);
	}
}
