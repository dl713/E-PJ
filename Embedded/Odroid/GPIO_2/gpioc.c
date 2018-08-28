#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	FILE *fp;
	char set_value[4];
	int toggle = 0;

	if((fp = fopen("/sys/class/gpio/export", "ab")) == NULL){
		printf("Cannot open export file.\n");
		return -1;
	}
	rewind(fp);
	strcpy(set_value, "31");
	fwrite(&set_value, sizeof(char), 3, fp);
	fclose(fp);

	printf("...direction set to output \n");

	if((fp = fopen("/sys/class/gpio/gpio31/direction", "rb+")) == NULL) {
		printf("Cannot open value file. \n");
		return -1;
	}
	rewind(fp);
	strcpy(set_value, "out");
	fwrite(&set_value, sizeof(char), 3, fp);
	fclose(fp);
	
	if((fp = fopen("/sys/class/gpio/gpio31/value", "rb+")) == NULL)
	{
		printf("Cannot open value file. \n");
		return -1;
	}

	rewind(fp);
	strcpy(set_value, "1");
	fwrite(&set_value, sizeof(char), 1, fp);
	fclose(fp);
	return 0;
}
