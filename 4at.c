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
	
	mkfifo(FIFO_REQUEST, 0666);
	mkfifo(FIFO_RESPONSE, 0666);

	printf("Server Starting\n");
	
	while(1){
		int request_fd = open(FIFO_REQUEST, O_RDONLY);
		int response_fd = open(FIFO_RESPONSE, O_WRONLY);
		
		read(request_fd, buffer, BUFFER_SIZE);
		printf("%s\n", buffer);

		char *response = "Recieved\n";
		write(response_fd, response, strlen(response));
	}
}
