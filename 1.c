#include<stdio.h>
#include<string.h>

char data[100], concat[117], frame[120], divident[18], crc[17];
char divisor[18] = "10001000000100001";

void calculate_crc(char *input, char *output){
	strcpy(divident, input);
	int len = strlen(input);
	for(int i = 0; i <= len - 17; i++){
		if(divident[i] == '1'){
			for(int j = 0; j < 17; j++){
				divident[i+j] = divident[i+j] == divisor[j]? '0':'1';
			} 
		}
	}
	strncpy(output, &divident[len - 16], 16);
	output[16] = '\0';
}

int main(){
	printf("Enter the data to be transfered: ");
	fgets(data, sizeof(data), stdin);
	strtok(data, "\n");

	strcpy(concat, data);
	strcat(concat, "0000000000000000");
	calculate_crc(concat, crc);

	printf("The data transfered is: %s%s \n", data, crc);

	printf("Enter the data recieved: ");
	fgets(frame, sizeof(frame), stdin);
	strtok(frame, "\n");

	calculate_crc(frame, divident);

	if(strcmp(divident, "0000000000000000") == 0){
		printf("No error\n");
	} else {
		printf("There is error\n");
	}

}
