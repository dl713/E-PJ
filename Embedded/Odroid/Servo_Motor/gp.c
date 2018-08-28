#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "gp.h"

void pinMode(char pin[], char mode[])
{
	FILE *fp;
	char buffer[10];
	char path[50];
	char set_value[10];

	if((fp = fopen("/sys/class/gpio/export","ab")) == NULL){
		printf("cannot open export file\n");
		return -1;
	}
	rewind(fp);
	strcpy(set_value,pin);
	fwrite(&set_value, sizeof(char), 3, fp);
	fclose(fp);
	
	strcpy(path,"/sys/class/gpio/gpio");
	strcat(path,pin);
	strcat(path,"/direction");
	
	if ((fp = fopen(path, "rb+")) == NULL) {
		printf("Cannot open export file\n");
		return -1;
	}
	rewind(fp);
	strcpy(set_value, mode);
	fwrite(&set_value, sizeof(char), 3, fp);
	fclose(fp);
}

void digitalWrite(char pin[], char mode[])
{
	FILE *fp;
	char buffer[10];
	char path[50];
	char set_value[10];

	strcpy(path,"/sys/class/gpio/gpio");
	strcat(path,pin);
	strcat(path,"/value");
	
	if((fp = fopen(path,"rb+")) == NULL){
			printf("Cannot open export file\n");
			return -1;
	}
	rewind(fp);
	strcpy(set_value,mode);
	fwrite(&set_value, sizeof(char), 1, fp);
	fclose(fp);
}
