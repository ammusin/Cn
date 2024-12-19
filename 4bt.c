#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

#define FIFO_REQUEST "/tmp/fifo_request"
#define FIFO_RESPONSE "/tmp/fifo_response"
#define BUFFER_SIZE 1024

int main(){
	char buffer[BUFFER_SIZE] = {0};

	printf("Client Started\n");

	while(1){
		int request_fd = open(FIFO_REQUEST, O_WRONLY);
		int response_fd = open(FIFO_RESPONSE, O_RDONLY);
		printf("Enter the message to be sent: ");
		fgets(buffer, BUFFER_SIZE, stdin);
		strtok(buffer, "\n");
		
		write(request_fd, buffer, strlen(buffer));

		read(response_fd, buffer, BUFFER_SIZE);
		printf("%s\n", buffer);
	}
}
