#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
	int socc;
	struct sockaddr_in serv_addr;
	char buffer[BUFFER_SIZE] = {0};
	
	socc = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	
	connect(socc, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	while(1){
		fgets(buffer, BUFFER_SIZE, stdin);
		buffer[strcspn(buffer, "\n")] = 0;
		send(socc, buffer, strlen(buffer), 0);
		
		read(socc, buffer, BUFFER_SIZE);
		printf("%s", buffer);
	}
}
